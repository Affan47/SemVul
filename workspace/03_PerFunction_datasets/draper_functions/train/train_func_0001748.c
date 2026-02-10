free_KRB_ERROR(KRB_ERROR *data)
{
free_krb5int32(&(data)->pvno);
free_MESSAGE_TYPE(&(data)->msg_type);
if((data)->ctime) {
free_KerberosTime((data)->ctime);
free((data)->ctime);
(data)->ctime = NULL;
}
if((data)->cusec) {
free_krb5int32((data)->cusec);
free((data)->cusec);
(data)->cusec = NULL;
}
free_KerberosTime(&(data)->stime);
free_krb5int32(&(data)->susec);
free_krb5int32(&(data)->error_code);
if((data)->crealm) {
free_Realm((data)->crealm);
free((data)->crealm);
(data)->crealm = NULL;
}
if((data)->cname) {
free_PrincipalName((data)->cname);
free((data)->cname);
(data)->cname = NULL;
}
free_Realm(&(data)->realm);
free_PrincipalName(&(data)->sname);
if((data)->e_text) {
der_free_general_string((data)->e_text);
free((data)->e_text);
(data)->e_text = NULL;
}
if((data)->e_data) {
der_free_octet_string((data)->e_data);
free((data)->e_data);
(data)->e_data = NULL;
}
}
