krb5_add_int_mem_ldap_mod(LDAPMod ***mods, char *attribute, int op, int value)
{
    int i=0;
    krb5_error_code      st=0;

    if ((st=krb5_add_member(mods, &i)) != 0)
        return st;

    (*mods)[i]->mod_type = strdup(attribute);
    if ((*mods)[i]->mod_type == NULL)
        return ENOMEM;

    (*mods)[i]->mod_op = op;
    (*mods)[i]->mod_values = calloc (2, sizeof(char *));
    if (((*mods)[i]->mod_values[0] = format_d(value)) == NULL)
        return ENOMEM;
    return 0;
}
