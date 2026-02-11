length_DigestInit(const DigestInit *data)
{
size_t ret = 0;
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += der_length_utf8string(&(data)->type);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
if((data)->channel){
size_t Top_tag_oldret = ret;
ret = 0;
{
size_t channel_tag_tag_oldret = ret;
ret = 0;
ret += der_length_utf8string(&((data)->channel)->cb_type);
ret += 1 + der_length_len (ret);
ret += channel_tag_tag_oldret;
}
{
size_t channel_tag_tag_oldret = ret;
ret = 0;
ret += der_length_utf8string(&((data)->channel)->cb_binding);
ret += 1 + der_length_len (ret);
ret += channel_tag_tag_oldret;
}
ret += 1 + der_length_len (ret);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
if((data)->hostname){
size_t Top_tag_oldret = ret;
ret = 0;
ret += der_length_utf8string((data)->hostname);
ret += 1 + der_length_len (ret);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
ret += 1 + der_length_len (ret);
return ret;
}
