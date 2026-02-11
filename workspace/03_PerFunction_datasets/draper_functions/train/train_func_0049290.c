inversePerm(const perm P, uint i) {
  uint j, elem;
  if (P->t==1) {
    j = get_field(P->bwdptrs,P->nbits,i);
  }
  else {
    j = i;
    while (((elem=get_field(P->elems,P->nbits,j)) != i)&&(!P->bmap->access(j)))
      j = elem;

    if (elem != i) {

      j = get_field(P->bwdptrs, P->nbits, P->bmap->rank1(j-1));
      while ((elem = get_field(P->elems,P->nbits,j))!= i)
        j = elem;
    }
  }
  return j;
}
