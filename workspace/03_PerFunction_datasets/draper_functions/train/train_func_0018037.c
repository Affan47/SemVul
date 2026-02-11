post_process_auth_passed_header(table *t, const char *key, const char * const val)
{
    if (strncasecmp(key, "Variable-", 9) == 0)
        key += 9;

    ap_table_setn(t, key, val);
    return 1;
}
