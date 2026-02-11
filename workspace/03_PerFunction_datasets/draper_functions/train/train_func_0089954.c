com_source(ptr) VARIABLE *ptr;


{
  char *name;

  FILE *save_in = math_in;


  name = var_to_string(ptr);


  if ((math_in = fopen(name,"r")) != NULL)
  {

     doread();
     fclose(math_in);
  }
  else
  {
    PrintOut( "Source: Can't open file, %s.\n",name );
  }

  math_in = save_in;
  FREEMEM(name);

  return (VARIABLE *)NULL;
}
