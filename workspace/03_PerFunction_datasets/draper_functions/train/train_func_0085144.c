eval(const PermutationScheme&p)const
{
double res= 0;
for(int i= j;i>=0;i--){
int cper= p.permute(i,base,coeff[i]);
res= (cper+res)/base;
}
return res;
}
