pbfp(long index) {
  if( (fptable == NULL) || ((int)index < 0) || ((int)index >= fptableSize) )
    return (FILE *) NULL;
  else
    return fptable[index];
}
