afr_sh_pending_to_delta (afr_private_t *priv, dict_t **xattr,
                         int32_t *delta_matrix[], unsigned char success[],
                         int child_count, afr_transaction_type type)
{

        int32_t  pending[3]  = {0,};
        void    *pending_raw = NULL;
        int      ret         = 0;
        int      i           = 0;
        int      j           = 0;
        int      k           = 0;


        for (i = 0; i < child_count; i++) {
                for (j = 0; j < child_count; j++) {
                        delta_matrix[i][j] = 0;
                }
        }

        for (i = 0; i < child_count; i++) {
                if (pending_raw)
                        pending_raw = NULL;

                for (j = 0; j < child_count; j++) {
                        ret = dict_get_ptr (xattr[i], priv->pending_key[j],
                                            &pending_raw);
                        if (ret < 0)
                                gf_log (THIS->name, GF_LOG_DEBUG,
                                        "Unable to get dict value.");
                        if (!success[j])
                                continue;

                        k = afr_index_for_transaction_type (type);

                        if (pending_raw != NULL) {
                                memcpy (pending, pending_raw, sizeof(pending));
                                delta_matrix[i][j] = -(ntoh32 (pending[k]));
                        } else {
                                delta_matrix[i][j]  = 0;
                        }

                }
        }
}
