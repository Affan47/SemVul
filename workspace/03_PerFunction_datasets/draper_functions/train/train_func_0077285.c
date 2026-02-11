posix_print_xattr (dict_t *this,
                   char *key,
                   data_t *value,
                   void *data)
{
        gf_log ("posix", GF_LOG_DEBUG,
                "(key/val) = (%s/%d)", key, data_to_int32 (value));
}
