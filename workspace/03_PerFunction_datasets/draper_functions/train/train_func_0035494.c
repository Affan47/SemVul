ldbm_config_db_durable_transactions_set(void *arg, void *value, char *errorbuf, int phase, int apply)
{
    struct ldbminfo *li = (struct ldbminfo *) arg;
    int retval = LDAP_SUCCESS;
    int val = (int) ((uintptr_t)value);

    if (apply) {
        li->li_dblayer_private->dblayer_durable_transactions = val;
    }

    return retval;
}
