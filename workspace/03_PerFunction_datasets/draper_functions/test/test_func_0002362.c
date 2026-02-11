krb5_principal_is_pku2u(krb5_context context, krb5_const_principal principal)
{
    return strcmp(principal->realm, KRB5_PKU2U_REALM_NAME) == 0;
}
