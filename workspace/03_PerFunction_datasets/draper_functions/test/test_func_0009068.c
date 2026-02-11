RsaFunction(const byte* in, word32 inLen, byte* out, word32* outLen,
                       int type, RsaKey* key)
{
    #define ERROR_OUT(x) { ret = x; goto done;}

    mp_int tmp;
    int    ret = 0;
    word32 keyLen, len;

    if (mp_init(&tmp) != MP_OKAY)
        return MP_INIT_E;

    if (mp_read_unsigned_bin(&tmp, (byte*)in, inLen) != MP_OKAY)
        ERROR_OUT(MP_READ_E);

    if (type == RSA_PRIVATE_DECRYPT || type == RSA_PRIVATE_ENCRYPT) {
        #ifdef RSA_LOW_MEM
            if (mp_exptmod(&tmp, &key->d, &key->n, &tmp) != MP_OKAY)
                ERROR_OUT(MP_EXPTMOD_E);
        #else
            #define INNER_ERROR_OUT(x) { ret = x; goto inner_done; }

            mp_int tmpa, tmpb;

            if (mp_init(&tmpa) != MP_OKAY)
                ERROR_OUT(MP_INIT_E);

            if (mp_init(&tmpb) != MP_OKAY) {
                mp_clear(&tmpa);
                ERROR_OUT(MP_INIT_E);
            }


            if (mp_exptmod(&tmp, &key->dP, &key->p, &tmpa) != MP_OKAY)
                INNER_ERROR_OUT(MP_EXPTMOD_E);


            if (mp_exptmod(&tmp, &key->dQ, &key->q, &tmpb) != MP_OKAY)
                INNER_ERROR_OUT(MP_EXPTMOD_E);


            if (mp_sub(&tmpa, &tmpb, &tmp) != MP_OKAY)
                INNER_ERROR_OUT(MP_SUB_E);

            if (mp_mulmod(&tmp, &key->u, &key->p, &tmp) != MP_OKAY)
                INNER_ERROR_OUT(MP_MULMOD_E);


            if (mp_mul(&tmp, &key->q, &tmp) != MP_OKAY)
                INNER_ERROR_OUT(MP_MUL_E);

            if (mp_add(&tmp, &tmpb, &tmp) != MP_OKAY)
                INNER_ERROR_OUT(MP_ADD_E);

        inner_done:
            mp_clear(&tmpa);
            mp_clear(&tmpb);

            if (ret != 0) return ret;

        #endif
    }
    else if (type == RSA_PUBLIC_ENCRYPT || type == RSA_PUBLIC_DECRYPT) {
        if (mp_exptmod(&tmp, &key->e, &key->n, &tmp) != MP_OKAY)
            ERROR_OUT(MP_EXPTMOD_E);
    }
    else
        ERROR_OUT(RSA_WRONG_TYPE_E);

    keyLen = mp_unsigned_bin_size(&key->n);
    if (keyLen > *outLen)
        ERROR_OUT(RSA_BUFFER_E);

    len = mp_unsigned_bin_size(&tmp);


    while (len < keyLen) {
        *out++ = 0x00;
        len++;
    }

    *outLen = keyLen;


    if (mp_to_unsigned_bin(&tmp, out) != MP_OKAY)
        ERROR_OUT(MP_TO_E);

done:
    mp_clear(&tmp);
    return ret;
}
