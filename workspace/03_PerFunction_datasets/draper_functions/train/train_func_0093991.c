MvgAutoWrapPrintf(DrawingWand *drawing_wand,const char *format,...)
{
  char
    buffer[MaxTextExtent];

  int
    formatted_length;

  va_list
    argp;

  va_start(argp,format);
#if defined(HAVE_VSNPRINTF)
  formatted_length=vsnprintf(buffer,sizeof(buffer)-1,format,argp);
#else
  formatted_length=vsprintf(buffer,format,argp);
#endif
  va_end(argp);
  buffer[sizeof(buffer)-1]=0;
  if (formatted_length < 0)
    {
      ThrowException(&drawing_wand->exception,DrawError,
		     UnableToPrint,format);
    }
  else
    {
      if (((drawing_wand->mvg_width + formatted_length) > 78) &&
          (buffer[formatted_length-1] != '\n'))
        (void) MvgPrintf(drawing_wand, "\n");
      (void) MvgPrintf(drawing_wand,"%s",buffer);
    }
  return(formatted_length);
}
