swap2(
  char *a[],
  char *b[],
  int i,
  int j
) {
  if (i==j) return;
  char*v;
  v=a[i]; a[i]=a[j]; a[j]=v;
  v=b[i]; b[i]=b[j]; b[j]=v;
}
