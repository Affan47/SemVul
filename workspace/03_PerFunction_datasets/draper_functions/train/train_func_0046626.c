_debug_bv(struct berval *bv)
{
        char *out;
        char octet[4];
        ber_len_t i;

        log_debug("---BER value HEX dump (size %u bytes)",
                  (unsigned int) bv->bv_len);

        if (bv->bv_len > 0) {
                out = (char *) calloc((3 * (bv->bv_len)) + 1, sizeof(char));
                if (!out) return;

                for (i = 1; i <= bv->bv_len; i++) {
                        snprintf(octet, 4, "%02x ",
                                 (unsigned char) bv->bv_val[i - 1]);
                        strcat(out, octet);
                }
                log_debug(out);
                free(out);
        }
}
