add_IDs_to_IDarray(ID ***dn_norm_sp_conflict, int *max, int i, char *strids)
{
    char *p, *next, *start;
    ID my_id;
    ID **conflict;
    ID *idp;
    ID *endp;
    size_t len;

    if ((NULL == dn_norm_sp_conflict) || (NULL == max) || (0 == *max)) {
        return 1;
    }
    p = PL_strchr(strids, ':');
    if (NULL == p) {
        LDAPDebug1Arg(LDAP_DEBUG_ANY,
                      "Format error: no ':' in %s\n", strids);
        return 1;
    }
    *p = '\0';
    my_id = (ID)strtol(strids, (char **)NULL, 10);
    if (!my_id) {
        LDAPDebug1Arg(LDAP_DEBUG_ANY, "Invalid ID in %s\n", strids);
        return 1;
    }

    if (NULL == *dn_norm_sp_conflict) {
        *dn_norm_sp_conflict = (ID **)slapi_ch_malloc(sizeof(ID *) * *max);
    } else if (*max == i + 1) {
        *max *= 2;
        *dn_norm_sp_conflict = (ID **)slapi_ch_realloc((char *)*dn_norm_sp_conflict,
                                                       sizeof(ID *) * *max);
    }
    conflict = *dn_norm_sp_conflict;

    len = strlen(strids);
    while (isspace(*(++p)));
    start = p;

    conflict[i] = (ID *)slapi_ch_calloc((len/2 + 2), sizeof(ID));
    idp = conflict[i];
    endp = idp + len/2 + 2;
    *idp++ = my_id;
    for (p = strtok_r(start, " \n", &next); p && (idp < endp);
         p = strtok_r(NULL, " \n", &next), idp++) {
        *idp = (ID)strtol(p, (char **)NULL, 10);
    }
    if (idp < endp) {
        *idp = 0;
    } else if (idp == endp) {
        conflict[i] = (ID *)slapi_ch_realloc((char *)conflict[i],
                                             (len/2 + 3) * sizeof(ID));
        idp = conflict[i];
        *(idp + len/2 + 2) = 0;
    }
    conflict[i+1] = NULL;
    return 0;
}
