length_KDCFastState(const KDCFastState *data)
{
size_t ret = 0;
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_KDCFastFlags(&(data)->flags);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += der_length_generalized_time(&(data)->expiration);
ret += 1 + der_length_len (ret);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_METHOD_DATA(&(data)->fast_state);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
if((data)->expected_pa_types){
size_t Top_tag_oldret = ret;
ret = 0;
{
size_t expected_pa_types_tag_tag_oldret = ret;
unsigned int n_expected_pa_types_tag_tag;
ret = 0;
for(n_expected_pa_types_tag_tag = ((data)->expected_pa_types)->len; n_expected_pa_types_tag_tag > 0; --n_expected_pa_types_tag_tag){
size_t expected_pa_types_tag_tag_for_oldret = ret;
ret = 0;
ret += length_PADATA_TYPE(&((data)->expected_pa_types)->val[n_expected_pa_types_tag_tag - 1]);
ret += expected_pa_types_tag_tag_for_oldret;
}
ret += expected_pa_types_tag_tag_oldret;
}
ret += 1 + der_length_len (ret);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
ret += 1 + der_length_len (ret);
return ret;
}
