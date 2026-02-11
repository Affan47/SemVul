GetElementIndex(struct CellType *cell,int i,int j)


{
  int elemind;

  if(cell->numbering == NUMBER_XY)
    elemind = cell->elem1st+(i-1) + (j-1)*cell->elemwidth;
  else if(cell->numbering == NUMBER_YX)
    elemind = cell->elem1st+(j-1) + (i-1)*cell->elemwidth;

  return(elemind);
}
