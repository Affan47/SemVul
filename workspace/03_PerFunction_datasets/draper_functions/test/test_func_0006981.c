length_EncryptedContentInfo(const EncryptedContentInfo *data)
{
size_t ret = 0;
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_ContentType(&(data)->contentType);
ret += Top_tag_oldret;
}
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_ContentEncryptionAlgorithmIdentifier(&(data)->contentEncryptionAlgorithm);
ret += Top_tag_oldret;
}
if((data)->encryptedContent){
size_t Top_tag_oldret = ret;
ret = 0;
ret += der_length_octet_string((data)->encryptedContent);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
ret += 1 + der_length_len (ret);
return ret;
}
