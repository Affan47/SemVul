SaveViewFactors(struct FemType *data,struct BoundaryType *bound,
		    char *prefix,int info)


{
  int i,j,ind[MAXNODESD1],sidelemtype;
  FILE *out;
  char filename[MAXFILESIZE];

  if(!bound->created) {
    printf("SaveViewFactors: boundary not created.\n");
    return(1);
  }
  if(bound->nosides == 0) {
    printf("SaveViewFactors: no sides on boundary.\n");
    return(2);
  }
  if(!bound->vfcreated) {
    printf("SaveViewFactors: view factors not created.\n");
    return(3);
  }

  AddExtension(prefix,filename,"vf");
  out = fopen(filename,"w");

  fprintf(out,"%d\n",bound->nosides);
  for(i=1; i <= bound->nosides; i++) {
    GetElementSide(bound->parent[i],bound->side[i],bound->normal[i],
		   data,ind,&sidelemtype);
    fprintf(out,"%-14.6le %-14.6le %-14.6le %-14.6le %-8d %-8d\n",
	    data->x[ind[0]],data->x[ind[1]],
	    data->y[ind[0]],data->y[ind[1]],
	    ind[0],ind[1]);
  }
  for(j=1; j <= bound->nosides; j++) {
    for(i=1; i <= bound->nosides; i++)
      fprintf(out,"%-14.6le ",bound->vf[j][i]);
    fprintf(out,"\n");
  }

  fclose(out);

  if(info) printf("View factors for %d sides were saved to file %s.\n",
		  bound->nosides,filename);
  return(0);
}
