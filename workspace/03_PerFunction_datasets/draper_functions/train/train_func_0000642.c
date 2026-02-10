header_dlmodEntry(struct variable *vp,
                  oid * name,
                  size_t * length,
                  int exact, size_t * var_len, WriteMethod ** write_method)
{
#define DLMODENTRY_NAME_LENGTH 12
    oid             newname[MAX_OID_LEN];
    int             result;
    struct dlmod   *dlm = NULL;
    unsigned int    dlmod_index;

    memcpy((char *) newname, (char *) vp->name,
           (int) vp->namelen * sizeof(oid));
    *write_method = 0;

    for (dlmod_index = 1; dlmod_index < dlmod_next_index; dlmod_index++) {
        dlm = dlmod_get_by_index(dlmod_index);

        DEBUGMSGTL(("dlmod", "dlmodEntry dlm: %p dlmod_index: %d\n",
                    dlm, dlmod_index));

        if (dlm) {
            newname[12] = dlmod_index;
            result = snmp_oid_compare(name, *length, newname,
                                      (int) vp->namelen + 1);

            if ((exact && (result == 0)) || (!exact && (result < 0)))
                break;
        }
    }

    if (dlmod_index >= dlmod_next_index) {
        if (dlmod_index == dlmod_next_index &&
            exact && vp->magic == DLMODSTATUS)

            *write_method = write_dlmodStatus;
        return NULL;
    }

    memcpy((char *) name, (char *) newname,
           ((int) vp->namelen + 1) * sizeof(oid));
    *length = vp->namelen + 1;
    *var_len = sizeof(long);
    return dlm;
}
