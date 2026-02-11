SetConnectedBoundary(struct FemType *data,struct BoundaryType *bound,
			 int bctype,int connecttype,int info)

{
  int i,j,k,l,bc,sideelemtype,sidenodes;
  int sideind[MAXNODESD1];


  for(bc=0;bc<MAXBOUNDARIES;bc++) {
    if(bound[bc].created == FALSE) continue;
    if(bound[bc].nosides == 0) continue;

    for(i=1;i<=bound[bc].nosides;i++) {
      if(bound[bc].types[i] != bctype) continue;

      if(!data->connectexist) {
	data->connect = Ivector(1,data->noknots);
	for(k=1;k<=data->noknots;k++)
	  data->connect[k] = 0;
	data->connectexist = TRUE;
      }

      GetElementSide(bound[bc].parent[i],bound[bc].side[i],bound[bc].normal[i],
		     data,sideind,&sideelemtype);
      sidenodes = sideelemtype%100;

      for(j=0;j<sidenodes;j++) {
	k = sideind[j];
	data->connect[k] = connecttype;
      }
    }
  }

  return(0);
}
