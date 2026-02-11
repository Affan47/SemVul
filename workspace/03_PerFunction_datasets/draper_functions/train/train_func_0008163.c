length_KRB_CRED(const KRB_CRED *data)
{
size_t ret = 0;
{
size_t Top_tag_tag_oldret = ret;
ret = 0;
ret += length_krb5int32(&(data)->pvno);
ret += 1 + der_length_len (ret);
ret += Top_tag_tag_oldret;
}
{
size_t Top_tag_tag_oldret = ret;
ret = 0;
ret += length_MESSAGE_TYPE(&(data)->msg_type);
ret += 1 + der_length_len (ret);
ret += Top_tag_tag_oldret;
}
{
size_t Top_tag_tag_oldret = ret;
ret = 0;
{
size_t tickets_tag_tag_oldret = ret;
unsigned int n_tickets_tag_tag;
ret = 0;
for(n_tickets_tag_tag = (&(data)->tickets)->len; n_tickets_tag_tag > 0; --n_tickets_tag_tag){
size_t tickets_tag_tag_for_oldret = ret;
ret = 0;
ret += length_Ticket(&(&(data)->tickets)->val[n_tickets_tag_tag - 1]);
ret += tickets_tag_tag_for_oldret;
}
ret += tickets_tag_tag_oldret;
}
ret += 1 + der_length_len (ret);
ret += 1 + der_length_len (ret);
ret += Top_tag_tag_oldret;
}
{
size_t Top_tag_tag_oldret = ret;
ret = 0;
ret += length_EncryptedData(&(data)->enc_part);
ret += 1 + der_length_len (ret);
ret += Top_tag_tag_oldret;
}
ret += 1 + der_length_len (ret);
ret += 1 + der_length_len (ret);
return ret;
}
