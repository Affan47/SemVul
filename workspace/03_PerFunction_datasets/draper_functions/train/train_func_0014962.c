view_parse_oid(oid * oidIndex, size_t oidLen,
               unsigned char **viewName, size_t * viewNameLen,
               oid ** subtree, size_t * subtreeLen)
{
    int             viewNameL, subtreeL, i;


    if ((oidLen <= 0) || (!oidIndex)) {
        return SNMP_ERR_INCONSISTENTNAME;
    }
    viewNameL = oidIndex[0];
    subtreeL = oidLen - viewNameL - 1;


    if (viewName == NULL || subtree == NULL) {
        return SNMP_ERR_RESOURCEUNAVAILABLE;
    }

    if (subtreeL < 0) {
        return SNMP_ERR_NOCREATION;
    }

    *viewName = (unsigned char *) malloc(viewNameL + 1);

    if (*viewName == NULL) {
        return SNMP_ERR_RESOURCEUNAVAILABLE;
    }

    *subtree = (oid *) malloc(subtreeL * sizeof(oid));
    if (*subtree == NULL) {
        free(*viewName);
        return SNMP_ERR_RESOURCEUNAVAILABLE;
    }

    *subtreeLen = subtreeL;
    *viewNameLen = viewNameL;

    for (i = 0; i < viewNameL; i++) {
        if (oidIndex[i + 1] > 255) {
            free(*viewName);
            free(*subtree);
            return SNMP_ERR_INCONSISTENTNAME;
        }
        viewName[0][i] = (unsigned char) oidIndex[i + 1];
    }
    viewName[0][viewNameL] = 0;

    for (i = 0; i < subtreeL; i++) {
        subtree[0][i] = (oid) oidIndex[i + viewNameL + 1];
    }

    return 0;
}
