glusterd_store_iter_get_matching (glusterd_store_iter_t *iter,
                              char  *key, char **value)
{
        int32_t ret = -1;
        char    *tmp_key = NULL;
        char    *tmp_value = NULL;

        ret = glusterd_store_iter_get_next (iter, &tmp_key, &tmp_value,
                                            NULL);
        while (!ret) {
                if (!strncmp (key, tmp_key, strlen (key))){
                        *value = tmp_value;
                        GF_FREE (tmp_key);
                        goto out;
                }
                GF_FREE (tmp_key);
                GF_FREE (tmp_value);
                ret = glusterd_store_iter_get_next (iter, &tmp_key,
                                                    &tmp_value, NULL);
        }
out:
        return ret;
}
