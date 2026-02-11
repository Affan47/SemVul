GetMarkers(int block, int constraint, int blockn[], int constraintn[],
		       int*m3){
  int i=0;
  while (blockn[i]==block && constraintn[i]==constraint){ i++;}
  *m3=i;
  return 0;
}
