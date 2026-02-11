IptAlloc(int  m,
              int  n,
              int  *ipt[],
              char *info)
{
  int i;

  if (n) {
    for (i=0; i<m; i++) {
      ipt[i]=(int*)calloc(n,sizeof(int));
      if (!ipt[i]){
	ExitProc(OutOfSpc,info);
	return 1;
      }
    }
  }
  return 0;
}
