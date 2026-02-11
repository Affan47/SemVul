ConcatenateImages(int argc,char **argv,
  ExceptionInfo *exception)
{
  FILE
    *input,
    *output;

  int
    c;

  register ssize_t
    i;


  output=fopen_utf8(argv[argc-1],"wb");
  if (output == (FILE *) NULL)
    {
      ThrowFileException(exception,FileOpenError,"UnableToOpenFile",
        argv[argc-1]);
      return(MagickFalse);
    }
  for (i=2; i < (ssize_t) (argc-1); i++)
  {
    input=fopen_utf8(argv[i],"rb");
    if (input == (FILE *) NULL)
      {
        ThrowFileException(exception,FileOpenError,"UnableToOpenFile",argv[i]);
        continue;
      }
    for (c=fgetc(input); c != EOF; c=fgetc(input))
      (void) fputc((char) c,output);
    (void) fclose(input);
    (void) remove_utf8(argv[i]);
  }
  (void) fclose(output);
  return(MagickTrue);
}
