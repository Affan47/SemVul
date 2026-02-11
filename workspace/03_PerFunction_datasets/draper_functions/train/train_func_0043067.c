errline(int n, int k, FILE *err)
{
  int spcnt, i;
  if( argv[0] ) fprintf(err,"%s",argv[0]);
  spcnt = lemonStrlen(argv[0]) + 1;
  for(i=1; i<n && argv[i]; i++){
    fprintf(err," %s",argv[i]);
    spcnt += lemonStrlen(argv[i])+1;
  }
  spcnt += k;
  for(; argv[i]; i++) fprintf(err," %s",argv[i]);
  if( spcnt<20 ){
    fprintf(err,"\n%*s^-- here\n",spcnt,"");
  }else{
    fprintf(err,"\n%*shere --^\n",spcnt-7,"");
  }
}
