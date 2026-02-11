validMatrix(){
  int i;

  for (i = 0; i < 3*n; i++)
    if ((degrees[i] != 0) && (degrees[i] != 1) && (degrees[i] != 2))
      return 0;

  for (i = 0; i < n; i++){
    if (!(degrees[3*i] == 0) && !(degrees[3*i+1] == 0) && !(degrees[3*i+2] == 0))
      return 0;
    if (degrees[3*i+1] == 0)
      return 0;
  }
  return 1;
}
