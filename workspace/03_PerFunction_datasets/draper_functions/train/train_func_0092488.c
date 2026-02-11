get_fixedbitl(byte **pres,const char *tag)
{
    if(check_tag(tag)==NOTOK){errr("Compressor::get_fixedbitl(byte *): check_tag failed");}
    int n=get_uint_vl(NBITS_NVALS);
    if(!n){*pres=NULL;return 0;}
    int nbits=get_uint(NBITS_NBITS_CHARVAL);
    if(verbose)printf("get_fixedbitl(byte):n%3d nbits:%2d\n",n,nbits);
    int i;
    byte *res=new byte[n];
    CHECK_MEM(res);
    for(i=0;i<n;i++)
    {
	res[i]=get_uint(nbits);
    }
    *pres=res;
    return(n);
}
