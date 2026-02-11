length_SignedData(const SignedData *data)
{
size_t ret = 0;
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_CMSVersion(&(data)->version);
ret += Top_tag_oldret;
}
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_DigestAlgorithmIdentifiers(&(data)->digestAlgorithms);
ret += Top_tag_oldret;
}
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_EncapsulatedContentInfo(&(data)->encapContentInfo);
ret += Top_tag_oldret;
}
if((data)->certificates){
size_t Top_tag_oldret = ret;
ret = 0;
{
size_t certificates_tag_oldret = ret;
unsigned int n_certificates_tag;
ret = 0;
for(n_certificates_tag = ((data)->certificates)->len; n_certificates_tag > 0; --n_certificates_tag){
size_t certificates_tag_for_oldret = ret;
ret = 0;
ret += length_heim_any(&((data)->certificates)->val[n_certificates_tag - 1]);
ret += certificates_tag_for_oldret;
}
ret += certificates_tag_oldret;
}
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
if((data)->crls){
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_heim_any((data)->crls);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_SignerInfos(&(data)->signerInfos);
ret += Top_tag_oldret;
}
ret += 1 + der_length_len (ret);
return ret;
}
