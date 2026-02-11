PNMInteger(Image *image,const unsigned int base)
{
  char
    *comment;

  int
    c;

  register char
    *p;

  size_t
    extent,
    value;


  extent=MaxTextExtent;
  comment=(char *) NULL;
  p=comment;
  do
  {
    c=ReadBlobByte(image);
    if (c == EOF)
      return(0);
    if (c == (int) '#')
      {


        if (comment == (char *) NULL)
          comment=AcquireString((char *) NULL);
        p=comment+strlen(comment);
        for ( ; (c != EOF) && (c != (int) '\n'); p++)
        {
          if ((size_t) (p-comment+1) >= extent)
            {
              extent<<=1;
              comment=(char *) ResizeQuantumMemory(comment,extent+MaxTextExtent,
                sizeof(*comment));
              if (comment == (char *) NULL)
                break;
              p=comment+strlen(comment);
            }
          c=ReadBlobByte(image);
          if (c != (int) '\n')
            {
              *p=(char) c;
              *(p+1)='\0';
            }
        }
        if (comment == (char *) NULL)
          return(0);
        continue;
      }
  } while (isdigit(c) == MagickFalse);
  if (comment != (char *) NULL)
    {
      (void) SetImageProperty(image,"comment",comment);
      comment=DestroyString(comment);
    }
  if (base == 2)
    return((size_t) (c-(int) '0'));


  value=0;
  do
  {
    value*=10;
    value+=c-(int) '0';
    c=ReadBlobByte(image);
    if (c == EOF)
      return(value);
  } while (isdigit(c) != MagickFalse);
  return(value);
}
