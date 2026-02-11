compile(char* filename)
{
 if (lua_openfile(filename)==NULL)
 {
  fprintf(stderr,"luac: cannot open ");
  perror(filename);
  exit(1);
 }
 do_compile();
 lua_closefile();
}
