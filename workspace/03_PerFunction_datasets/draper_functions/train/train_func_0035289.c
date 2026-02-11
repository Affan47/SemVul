length_KERB_TGS_REP_IN(const KERB_TGS_REP_IN *data)
{
size_t ret = 0;
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += der_length_octet_string(&(data)->cache);
ret += 1 + der_length_len (ret);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
if((data)->subkey){
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_EncryptionKey((data)->subkey);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_KERB_CRED(&(data)->in_cred);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_TGS_REP(&(data)->t);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
ret += 1 + der_length_len (ret);
return ret;
}
