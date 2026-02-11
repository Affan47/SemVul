cut_super_hmdf_table(Hmdf_table *root)
{
    Hmdf_table *chmdf,*nhmdf;

    for(chmdf=root->children;chmdf!=NULL;chmdf=chmdf->brothers){
      for(nhmdf=chmdf;nhmdf!=NULL;nhmdf=nhmdf->next){
	nhmdf->parent = NULL;
      }
    }
    for(chmdf=root;chmdf!=NULL;chmdf=chmdf->next){
	chmdf->children = NULL;
    }
}
