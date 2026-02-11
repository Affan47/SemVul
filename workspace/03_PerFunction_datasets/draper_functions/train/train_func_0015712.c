dht_aggregate (dict_t *this, char *key, data_t *value, void *data)
{
        dict_t  *dst  = NULL;
        int64_t *ptr  = 0, *size = NULL;
        int32_t  ret  = -1;
        data_pair_t  *data_pair = NULL;

        dst = data;

        if (strcmp (key, GF_XATTR_QUOTA_SIZE_KEY) == 0) {
                ret = dict_get_bin (dst, key, (void **)&size);
                if (ret < 0) {
                        size = GF_CALLOC (1, sizeof (int64_t),
                                          gf_common_mt_char);
                        if (size == NULL) {
                                gf_log ("dht", GF_LOG_WARNING,
                                        "memory allocation failed");
                                return;
                        }
                        ret = dict_set_bin (dst, key, size, sizeof (int64_t));
                        if (ret < 0) {
                                gf_log ("dht", GF_LOG_WARNING,
                                        "dht aggregate dict set failed");
                                GF_FREE (size);
                                return;
                        }
                }

                ptr = data_to_bin (value);
                if (ptr == NULL) {
                        gf_log ("dht", GF_LOG_WARNING, "data to bin failed");
                        return;
                }

                *size = hton64 (ntoh64 (*size) + ntoh64 (*ptr));
        } else {

                if (!strncmp (key, "user.", strlen ("user."))) {
                        ret = dict_lookup (dst, key, &data_pair);
                        if (!ret && data) {
                                ret = is_data_equal (data_pair->value, value);
                                if (!ret)
                                        gf_log ("dht", GF_LOG_WARNING,
                                                "xattr mismatch for %s", key);
                        }
                }
                ret = dict_set (dst, key, value);
                if (ret)
                        gf_log ("dht", GF_LOG_WARNING, "xattr dict set failed");
        }

        return;
}
