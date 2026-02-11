Compress_main(Compressor &out)
{
    if(debug>1){verbose=1;}
    if(verbose){printf("WordDBPage::Compress_main: starting compression\n");}

    if(pg->type!=5 && pg->type!=3){    printf("pg->type:%3d\n",pg->type);return NOTOK;}


    int j;


    int *nums    =new int[nk*nnums];
    CHECK_MEM(nums);
    int *nums_pos=new int[   nnums];
    CHECK_MEM(nums_pos);

    for(j=0;j<nnums;j++){nums_pos[j]=0;}


    HtVector_byte worddiffs;


    if(nk>0)
    {
	Compress_extract_vals_wordiffs(nums,nums_pos,nnums,worddiffs);
	if(verbose)Compress_show_extracted(nums,nums_pos,nnums,worddiffs);
    }


    Compress_header(out);


    int nkeysleft=nk;
    if(nkeysleft>0)
    {
	compress_key(out,0);
	if(type==P_LBTREE){compress_data(out,0);}
	nkeysleft--;
    }
    if(nkeysleft>0 && type==P_IBTREE){compress_key(out,1);nkeysleft--;}

    if(nkeysleft>0)
    {


	Compress_vals(out,nums,nums_pos,nnums);


	int size=out.put_fixedbitl(worddiffs.begin(),worddiffs.size(),"WordDiffs");
	if(verbose)printf("compressed wordiffs : %3d values: %4d bits %4f bytes\n",worddiffs.size(),size,size/8.0);

    }


    delete [] nums ;
    delete [] nums_pos;

    return OK;
}
