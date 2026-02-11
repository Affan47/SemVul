length_PA_ENC_SAM_RESPONSE_ENC(const PA_ENC_SAM_RESPONSE_ENC *data)
{
size_t ret = 0;
{
size_t Top_tag_oldret = ret;
ret = 0;
ret += length_krb5int32(&(data)->sam_nonce);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
if((data)->sam_sad){
size_t Top_tag_oldret = ret;
ret = 0;
ret += der_length_general_string((data)->sam_sad);
ret += 1 + der_length_len (ret);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
ret += 1 + der_length_len (ret);
return ret;
}
