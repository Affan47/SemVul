length_hdb_keyset(const hdb_keyset *data)
{
size_t ret = 0;
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += der_length_unsigned(&(data)->kvno);
ret += 1 + der_length_len (ret);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_Keys(&(data)->keys);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
if((data)->set_time){
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_KerberosTime((data)->set_time);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
ret += 1 + der_length_len (ret);
return ret;
}
