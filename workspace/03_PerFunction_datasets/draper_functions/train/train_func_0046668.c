ldbm_config_dbcachesize_set(void *arg, void *value, char *errorbuf, int phase, int apply)
{
    struct ldbminfo *li = (struct ldbminfo *) arg;
    int retval = LDAP_SUCCESS;
    size_t val = (size_t) value;

    if (apply) {


#define DBDEFMINSIZ     500000
        if (val < DBDEFMINSIZ) {
            LDAPDebug( LDAP_DEBUG_ANY,"WARNING: cache too small, increasing to %dK bytes\n", DBDEFMINSIZ/1000, 0, 0);
            val = DBDEFMINSIZ;
        }

        if (CONFIG_PHASE_RUNNING == phase) {
            li->li_new_dbcachesize = val;
            LDAPDebug(LDAP_DEBUG_ANY, "New db cache size will not take affect until the server is restarted\n", 0, 0, 0);
        } else {
            li->li_new_dbcachesize = val;
            li->li_dbcachesize = val;
        }

    }

    return retval;
}
