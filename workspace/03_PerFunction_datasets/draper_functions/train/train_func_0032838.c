length_Key(const Key *data)
{
size_t ret = 0;
if((data)->mkvno){
size_t Top_tag_oldret = ret;
ret = 0;
ret += der_length_unsigned((data)->mkvno);
ret += 1 + der_length_len (ret);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_EncryptionKey(&(data)->key);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
if((data)->salt){
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_Salt((data)->salt);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
ret += 1 + der_length_len (ret);
return ret;
}
