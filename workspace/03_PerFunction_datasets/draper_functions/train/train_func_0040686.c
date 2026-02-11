GetKnotIndex(struct CellType *cell,int i,int j)


{
  int ind,aid,maxj;

  if(cell->numbering == NUMBER_1D) {
    ind = cell->left1st;
    if(cell->nonodes == 2)
      ind += i;
    else if(cell->nonodes == 3)
      ind += 2*i;
    else if(cell->nonodes == 4)
      ind += 3*i;
    return(ind);
  }

  if(cell->numbering == NUMBER_XY)
    maxj = cell->yelem;
  else if(cell->numbering == NUMBER_YX) {
    aid = j; j = i; i = aid;
    maxj = cell->xelem;
  }

  if(j == 0)
    ind = cell->left1st;
  else if (j == maxj)
    ind = cell->leftlast;
  else
    ind = cell->left2nd + (j-1) * cell->levelwidth;

  if(cell->nonodes == 4)
    ind += i;
  else if(cell->nonodes == 5)
    ind += i;
  else if(cell->nonodes == 8 || cell->nonodes == 9)
    ind += 2*i;
  else if(cell->nonodes == 12 || cell->nonodes == 16)
    ind += 3*i;

  return(ind);
}
