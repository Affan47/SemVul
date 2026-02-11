compile(char* filename)
{
 FILE* f= (filename==NULL) ? stdin : fopen(filename, "r");
 if (f==NULL)
 {
  fprintf(stderr,"luac: cannot open ");
  perror(filename);
  exit(1);
 }
 else
 {
  ZIO z;
  zFopen(&z,f);
  luaI_setparsedfile(filename?filename:"(stdin)");
  do_compile(&z);
  fclose(f);
 }
}
