length_DistributionPointName(const DistributionPointName *data)
{
size_t ret = 0;
switch((data)->element) {
case choice_DistributionPointName_fullName:
{
size_t Top_oldret = ret;
ret = 0;
{
size_t fullName_tag_oldret = ret;
unsigned int n_fullName_tag;
ret = 0;
for(n_fullName_tag = (&(data)->u.fullName)->len; n_fullName_tag > 0; --n_fullName_tag){
size_t fullName_tag_for_oldret = ret;
ret = 0;
ret += length_GeneralName(&(&(data)->u.fullName)->val[n_fullName_tag - 1]);
ret += fullName_tag_for_oldret;
}
ret += fullName_tag_oldret;
}
ret += 1 + der_length_len (ret);
ret += Top_oldret;
}
break;
case choice_DistributionPointName_nameRelativeToCRLIssuer:
{
size_t Top_oldret = ret;
ret = 0;
ret += length_RelativeDistinguishedName(&(data)->u.nameRelativeToCRLIssuer);
ret += 1 + der_length_len (ret);
ret += Top_oldret;
}
break;
}
return ret;
}
