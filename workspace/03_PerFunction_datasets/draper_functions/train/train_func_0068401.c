parse_op_key(const char *key, char **rsc_id, char **op_type, int *interval)
{
    char *notify = NULL;
    char *mutable_key = NULL;
    char *mutable_key_ptr = NULL;
    int len = 0, offset = 0, ch = 0;

    CRM_CHECK(key != NULL, return FALSE);

    *interval = 0;
    len = strlen(key);
    offset = len - 1;

    crm_trace("Source: %s", key);

    while (offset > 0 && isdigit(key[offset])) {
        int digits = len - offset;

        ch = key[offset] - '0';
        CRM_CHECK(ch < 10, return FALSE);
        CRM_CHECK(ch >= 0, return FALSE);
        while (digits > 1) {
            digits--;
            ch = ch * 10;
        }
        *interval += ch;
        offset--;
    }

    crm_trace("  Interval: %d", *interval);
    CRM_CHECK(key[offset] == '_', return FALSE);

    mutable_key = strdup(key);
    mutable_key_ptr = mutable_key_ptr;
    mutable_key[offset] = 0;
    offset--;

    while (offset > 0 && key[offset] != '_') {
        offset--;
    }

    CRM_CHECK(key[offset] == '_', free(mutable_key);
              return FALSE);

    mutable_key_ptr = mutable_key + offset + 1;

    crm_trace("  Action: %s", mutable_key_ptr);

    *op_type = strdup(mutable_key_ptr);

    mutable_key[offset] = 0;
    offset--;

    CRM_CHECK(mutable_key != mutable_key_ptr, free(mutable_key);
              return FALSE);

    notify = strstr(mutable_key, "_post_notify");
    if (notify && safe_str_eq(notify, "_post_notify")) {
        notify[0] = 0;
    }

    notify = strstr(mutable_key, "_pre_notify");
    if (notify && safe_str_eq(notify, "_pre_notify")) {
        notify[0] = 0;
    }

    crm_trace("  Resource: %s", mutable_key);
    *rsc_id = mutable_key;

    return TRUE;
}
