post_process_auth_passed_compat_header(table *t, const char *key, const char * const val)
{
    if (strncasecmp(key, "Variable-", 9) == 0)
        ap_table_setn(t, key + 9, val);

    return 1;
}
