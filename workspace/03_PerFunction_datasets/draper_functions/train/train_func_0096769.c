CreateMarkovStateVariable_File(FILE *f, char *filename)
{
  FILE *f_in;
  char *str, *str_old;
  int err;
  TMarkovStateVariable *sv=(TMarkovStateVariable*)NULL;


  if (f)
    f_in=f;
  else
    if (!(f_in=fopen(filename,"rt")))
      {
	err=SWITCHIO_FILE_ERROR;
	return (TMarkovStateVariable*)NULL;
      }


  if (err=SetFilePosition(f_in,(char*)NULL,str="//== Markov State Variables with Simple Restrictions ==//"))
    {
      if (err=SetFilePosition(f_in,(char*)NULL,str_old="//== Flat Independent Markov States and Simple Restrictions ==//"))
	ReadError((char*)NULL,str,err);
      else
	printf("Warning CreateMarkovStateVariable_File():  Old file format for file type.\n");
    }
  sv=CreateMarkovStateVariable_Simple(f_in,"");


  if (!f && f_in) fclose(f_in);


  return sv;
}
