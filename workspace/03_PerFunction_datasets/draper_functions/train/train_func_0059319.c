length_BasicConstraints(const BasicConstraints *data)
{
size_t ret = 0;
if((data)->cA){
size_t Top_tag_oldret = ret;
ret = 0;
ret += 1;
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
if((data)->pathLenConstraint){
size_t Top_tag_oldret = ret;
ret = 0;
ret += der_length_unsigned((data)->pathLenConstraint);
ret += 1 + der_length_len (ret);
ret += Top_tag_oldret;
}
ret += 1 + der_length_len (ret);
return ret;
}
