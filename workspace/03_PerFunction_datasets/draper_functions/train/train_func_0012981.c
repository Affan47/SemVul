print_debug2(Array_dim_info *ad_pt)
{
  int i;

  for(i = 0;i < ad_pt->dim;i++){
    fprintf(stderr,"%d:%d",
	    min_IntSet(ad_pt->dim_info[i]),
	    max_IntSet(ad_pt->dim_info[i]));
    if(i == ad_pt->dim-1){
      fprintf(stderr,"\n");
    }else{
      fprintf(stderr," ");
    }
  }
}
