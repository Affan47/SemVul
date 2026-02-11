pr_bv_member(IntSet      bv,
                  int         len,
                  Boolean     bra)
{
    int i;

    if(bra)
      fprintf(fp,"{");
    else
      fprintf(fp,"(");
    for(i = 0 ;i <= len; i++){
      if(in_IntSet(bv,i)){
	fprintf(fp," %d",i);
      }
    }
    if(bra)
      fprintf(fp," }");
    else
      fprintf(fp," )");
}
