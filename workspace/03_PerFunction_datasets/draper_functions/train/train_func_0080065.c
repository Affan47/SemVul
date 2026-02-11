RemoveUnusedNodes(struct FemType *data,int info)
{
  int i,j,k;
  int noelements,noknots,nonodes,activeknots;
  int *indx;

  noelements = data->noelements;
  noknots = data->noknots;

  indx = Ivector(1,noknots);
  for(i=1;i<=noknots;i++) indx[i] = 0;

  for(j=1;j<=noelements;j++) {
    nonodes = data->elementtypes[j] % 100;
    for(i=0;i<nonodes;i++)
      indx[ data->topology[j][i] ] = 1;
  }

  activeknots = 0;
  for(i=1;i<=noknots;i++) {
    if(indx[i]) {
      activeknots += 1;
      indx[i] = activeknots;
    }
  }

  if( noknots == activeknots) {
    if(info) printf("All %d nodes were used by the mesh elements\n",noknots);
    return(1);
  }

  if(info) printf("Removing %d unused nodes (out of %d) from the mesh\n",noknots-activeknots,noknots);

  for(j=1;j<=noelements;j++) {
    nonodes = data->elementtypes[j] % 100;
    for(i=0;i<nonodes;i++)
      data->topology[j][i] = indx[ data->topology[j][i] ];
  }

  for(i=1;i<=noknots;i++) {
    j = indx[i];
    if(!j) continue;
    data->x[j] = data->x[i];
    data->y[j] = data->y[i];
    if(data->dim == 3) data->z[j] = data->z[i];
  }
  data->noknots = activeknots;

  free_Ivector(indx,1,noknots);

  return(0);
}
