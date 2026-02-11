ExecuteSubCommand(const ImageInfo *image_info,
  int argc,char **argv,char **metadata,ExceptionInfo *exception)
{
  unsigned int
    status;

  ImageInfo
    *clone_info;

  char
    *text = (char *) NULL;;

  clone_info=CloneImageInfo(image_info);
  status=MagickCommand(clone_info,argc,argv,metadata,exception);
  if (metadata != (char **) NULL)
    text=*metadata;
  if (text != (char *) NULL)
    {
      if (strlen(text))
        {
          (void) fputs(text,stdout);
          (void) fputc('\n',stdout);
          (void) fflush(stdout);
        }
      MagickFreeMemory(text);
      *metadata=text;
    }
  DestroyImageInfo(clone_info);
  return status;
}
