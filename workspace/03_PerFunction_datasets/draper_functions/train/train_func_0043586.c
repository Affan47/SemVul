printchunk(int i, int chunklinelen, char *chunkname) {
  int j;
  int k;
  int linelen;
  char *getname;
  int getlen = 0;
  if (DEBUG==3) { printf("===   \\start{%s}   ===\n",chunkname); }
  for (k=i+chunklinelen+1; ((linelen=nextline(k)) != -1); ) {
    if ((getlen=foundGetchunk(k,linelen)) > 0) {
       getname = getChunkname(k,getlen);
       getchunk(getname);
       free(getname);
       k=k+getlen+12l;
    } else {
      if ((linelen >= 11) && (foundEnd(k,chunkname) == 1)) {
      if (DEBUG==3) { printf("===   \\end{%s}   ===\n",chunkname); }
      return(k+12);
    } else {
      if (DEBUG==2) {
        printf("======== printchunk else %d %d\n",k,linelen);
      }
      printline(k,linelen);
      k=k+linelen+1;
    }
  }}
  if (DEBUG==2) {
     printf("=================\\out{%s} %d\n",chunkname,k);
  }
  return(k);
}
