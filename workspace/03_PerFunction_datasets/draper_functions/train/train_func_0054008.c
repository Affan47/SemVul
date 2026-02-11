get_fixedbitl(unsigned int *res,int n)
{
    int nbits=get_uint_vl(NBITS_NBITS_VAL);
    if(verbose)printf("get_fixedbitl(uint):n%3d nbits:%2d\n",n,nbits);
    int i;
    for(i=0;i<n;i++)
    {
	res[i]=get_uint(nbits);
    }
}
