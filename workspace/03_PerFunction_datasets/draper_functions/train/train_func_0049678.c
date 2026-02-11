krb5_ldap_get_time(LDAP *ld, LDAPMessage *ent, char *attribute,
                   krb5_timestamp *rettime, krb5_boolean *attr_present)
{
    char                         **values=NULL;
    krb5_error_code              st=0;

    *rettime = 0;
    *attr_present = FALSE;

    values=ldap_get_values(ld, ent, attribute);
    if (values != NULL) {
        if (values[0] != NULL) {
            *attr_present = TRUE;
            st = getepochtime(values[0], rettime);
        }
        ldap_value_free(values);
    }
    return st;
}
