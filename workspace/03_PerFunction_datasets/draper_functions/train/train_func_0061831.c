DsaSign(const byte* digest, byte* out, DsaKey* key, RNG* rng)
{
    mp_int k, kInv, r, s, H;
    int    ret = 0, sz;
    byte   buffer[DSA_HALF_SIZE];

    if (mp_init_multi(&k, &kInv, &r, &s, &H, 0) != MP_OKAY)
        return MP_INIT_E;

    sz = min(sizeof(buffer), mp_unsigned_bin_size(&key->q));


    RNG_GenerateBlock(rng, buffer, sz);
    buffer[0] |= 0x0C;

    if (mp_read_unsigned_bin(&k, buffer, sz) != MP_OKAY)
        ret = MP_READ_E;

    if (mp_cmp_d(&k, 1) != MP_GT)
        ret = MP_CMP_E;


    if (ret == 0 && mp_invmod(&k, &key->q, &kInv) != MP_OKAY)
        ret = MP_INVMOD_E;


    if (ret == 0 && mp_exptmod(&key->g, &k, &key->p, &r) != MP_OKAY)
        ret = MP_EXPTMOD_E;

    if (ret == 0 && mp_mod(&r, &key->q, &r) != MP_OKAY)
        ret = MP_MOD_E;


    if (ret == 0 && mp_read_unsigned_bin(&H, digest,SHA_DIGEST_SIZE) != MP_OKAY)
        ret = MP_READ_E;


    if (ret == 0 && mp_mul(&key->x, &r, &s) != MP_OKAY)
        ret = MP_MUL_E;

    if (ret == 0 && mp_add(&s, &H, &s) != MP_OKAY)
        ret = MP_ADD_E;

    if (ret == 0 && mp_mulmod(&s, &kInv, &key->q, &s) != MP_OKAY)
        ret = MP_MULMOD_E;


    if (ret == 0)  {
        int rSz = mp_unsigned_bin_size(&r);
        int sSz = mp_unsigned_bin_size(&s);

        if (rSz == DSA_HALF_SIZE - 1) {
            out[0] = 0;
            out++;
        }

        if (mp_to_unsigned_bin(&r, out) != MP_OKAY)
            ret = MP_TO_E;
        else {
            if (sSz == DSA_HALF_SIZE - 1) {
                out[rSz] = 0;
                out++;
            }
            ret = mp_to_unsigned_bin(&s, out + rSz);
        }
    }

    mp_clear(&H);
    mp_clear(&s);
    mp_clear(&r);
    mp_clear(&kInv);
    mp_clear(&k);

    return ret;
}
