free_EncKrbPrivPart(EncKrbPrivPart *data)
{
der_free_octet_string(&(data)->user_data);
if((data)->timestamp) {
free_KerberosTime((data)->timestamp);
free((data)->timestamp);
(data)->timestamp = NULL;
}
if((data)->usec) {
free_krb5int32((data)->usec);
free((data)->usec);
(data)->usec = NULL;
}
if((data)->seq_number) {
free_krb5uint32((data)->seq_number);
free((data)->seq_number);
(data)->seq_number = NULL;
}
if((data)->s_address) {
free_HostAddress((data)->s_address);
free((data)->s_address);
(data)->s_address = NULL;
}
if((data)->r_address) {
free_HostAddress((data)->r_address);
free((data)->r_address);
(data)->r_address = NULL;
}
}
