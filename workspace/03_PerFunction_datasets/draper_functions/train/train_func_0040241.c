set_hmac(int sock, struct auth_context *actx)
{
        struct sctp_hmacalgo *hmac;
        int idlen = 1, struct_sz;
        int ret = 0;

        if (actx->auth_hmac_id != SCTP_AUTH_HMAC_ID_SHA1)
                idlen = 2;

        struct_sz = sizeof(struct sctp_hmacalgo) + idlen*sizeof(uint16_t);
        hmac = mem_zalloc(struct_sz);


        if (idlen == 2)
                hmac->shmac_idents[1] = SCTP_AUTH_HMAC_ID_SHA1;
        hmac->shmac_idents[0] = actx->auth_hmac_id;
        hmac->shmac_number_of_idents = idlen;

        TRACE("Setting %d HMAC ident(s)\n", hmac->shmac_number_of_idents);

        if (setsockopt(sock, SOL_SCTP,SCTP_HMAC_IDENT,
                                hmac, struct_sz) != 0) {
                ERROR("Unable to set HMAC_IDENT : %s\n", strerror(errno));
                ret = -1;
        }
        mem_free(hmac);
        return ret;
}
