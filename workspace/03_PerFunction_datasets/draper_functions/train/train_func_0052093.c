set_hmdf_table(int pc, int pe, Clustering_info_tmp *tmp_clust)
{
  Hmdf_table           *hpt;
  Clustering_info      *ci_ptr;
  Pc_info              *pi_ptr;
  Clustering_info_tmp  *tmp_c;
  Pc_info_tmp          *tmp_p;
  int                  i;

  hpt = alloc_hmdf_table();

  hpt->pc_num = pc;
  hpt->pe_num = pe;

  for(tmp_c=tmp_clust, i=0; tmp_c != NULL; tmp_c=tmp_c->next)
    i++;
  hpt->clustering_num = i;
  hpt->clustering = (Clustering_info *)calloc(i+1,sizeof(Clustering_info));
  if(hpt == NULL){
    fprintf(stderr,"No more room for Clustering_info.\n");
    exit(-1);
  }

  for(tmp_c=tmp_clust,ci_ptr=hpt->clustering; tmp_c!=NULL; tmp_c=tmp_c->next,ci_ptr++){
    ci_ptr->peofcp = tmp_c->peofcp;
    for(tmp_p=tmp_c->pcinfo,i=0; tmp_p!=NULL; tmp_p=tmp_p->next)
      i++;
    ci_ptr->pcinfo = (Pc_info *)calloc(i+1,sizeof(Pc_info));
    if(ci_ptr->pcinfo == NULL){
      fprintf(stderr,"No more room for Pc_info.\n");
      exit(-1);
    }
    for(tmp_p=tmp_c->pcinfo,pi_ptr=ci_ptr->pcinfo; tmp_p!=NULL; tmp_p=tmp_p->next,pi_ptr++){
      pi_ptr->fstpe = tmp_p->fstpe;
      pi_ptr->ch    = tmp_p->ch;
    }
  }

  free_clustering_info_tmp(tmp_clust);

  return hpt;
}
