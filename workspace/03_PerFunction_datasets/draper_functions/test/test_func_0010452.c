mean(double **v,unsigned long nv,unsigned long nh,int offset1,int offset2)
{
  double s=0;
  unsigned long i,j;
  for(i=offset1;i<(nv+offset1);i++){
    for(j=offset2;j<(nh+offset2);j++){
      s+=v[i][j];
    }
  }
  return (s/(double)(nv*nh));
}
