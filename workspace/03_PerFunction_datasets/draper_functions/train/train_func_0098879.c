remove(GAGenome * r)
{
  GAGenome * removed=(GAGenome *)0;
  if(r == (GAGenome *)0) return removed;
  unsigned int i;
  for(i=0; i<n && rind[i] != r; i++);
  if(i < n) removed = remove(i, RAW);
  return removed;
}
