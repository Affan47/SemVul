ntru_decrypt(uint8_t *enc, NtruEncKeyPair *kp, const NtruEncParams *params, uint8_t *dec, uint16_t *dec_len) {
    uint16_t N = params->N;
    uint16_t q = params->q;
    uint16_t db = params->db;
    uint16_t max_len_bytes = ntru_max_msg_len(params);
    uint16_t dm0 = params->dm0;

    if (max_len_bytes > 255)
        return NTRU_ERR_INVALID_MAX_LEN;

    uint16_t blen = db / 8;
    uint8_t retcode = NTRU_SUCCESS;

    NtruIntPoly e;
    ntru_from_arr(enc, N, q, &e);
    NtruIntPoly ci;
    ntru_decrypt_poly(&e, &kp->priv, q, &ci);

    if (!ntru_check_rep_weight(&ci, dm0))
        retcode = NTRU_ERR_DM0_VIOLATION;

    NtruIntPoly cR = e;
    ntru_sub_int(&cR, &ci);
    ntru_mod(&cR, q);

    uint16_t coR4_len = (N*2+7) / 8;
    uint8_t coR4[coR4_len];
    ntru_to_arr4(&cR, (uint8_t*)&coR4);

    NtruIntPoly mask;
    ntru_MGF((uint8_t*)&coR4, coR4_len, params, &mask);
    NtruIntPoly cmtrin = ci;
    ntru_sub_int(&cmtrin, &mask);
    ntru_mod3(&cmtrin);
    uint16_t cM_len_bits = (N*3+1) / 2;
    uint16_t cM_len_bytes = (cM_len_bits+7) / 8;
    uint8_t cM[cM_len_bytes+3];
    if (!ntru_to_sves(&cmtrin, (uint8_t*)&cM))
        retcode = NTRU_ERR_INVALID_ENCODING;

    uint8_t cb[blen];
    uint8_t *cM_head = cM;
    memcpy(cb, cM_head, blen);
    cM_head += blen;
    uint8_t cl = *cM_head;
    cM_head++;
    if (cl > max_len_bytes)
        retcode = NTRU_ERR_MSG_TOO_LONG;

    memcpy(dec, cM_head, cl);
    cM_head += cl;

    uint8_t *i;
    for (i=cM_head; i<cM+cM_len_bytes; i++)
        if (*i)
            retcode = NTRU_ERR_NO_ZERO_PAD;

    uint16_t sdata_len = sizeof(params->oid) + cl + blen + db/8;
    uint8_t sdata[sdata_len];
    ntru_get_seed(dec, cl, &kp->pub.h, (uint8_t*)&cb, params, (uint8_t*)&sdata);

    NtruPrivPoly cr;
    ntru_gen_blind_poly((uint8_t*)&sdata, sdata_len, params, &cr);
    NtruIntPoly cR_prime;
    ntru_mult_priv(&cr, &kp->pub.h, &cR_prime, q);
    if (!ntru_equals_int(&cR_prime, &cR))
        retcode = NTRU_ERR_INVALID_ENCODING;

    *dec_len = cl;
    return retcode;
}
