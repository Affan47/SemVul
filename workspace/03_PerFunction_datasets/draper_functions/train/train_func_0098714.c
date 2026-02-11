CalculateIndexwidth(struct FemType *data,int indxis,int *indx)
{
  int i,ind,nonodes,indexwidth;
  int imax,imin,element;


  indexwidth = 0;

  for(element=1; element <= data->noelements; element++) {
    imin = data->noknots;
    imax = 0;
    nonodes = data->elementtypes[element]%100;
    for(i=0;i<nonodes;i++) {
      ind = data->topology[element][i];
      if(indxis) ind = indx[ind];
      if(ind == 0) continue;
      if(ind > imax) imax = ind;
      if(ind < imin) imin = ind;
    }
    if(imax-imin > indexwidth)
      indexwidth = imax-imin;
  }

  if(!indxis) data->indexwidth = indexwidth;
  return(indexwidth);
}
