FormatSize(const magick_int64_t size,char *format)
{
  double
    length;

  register unsigned int
    i;

  length=size;
  for (i=0; length > 1024; i++)
    length/=1024.0;
  if (i > 0)
    FormatString(format,"%.1f",length);
  else
    FormatString(format,"%.0f",length);
  switch (i)
    {
    default: break;
    case 0: break;
    case 1: (void) strcat(format,"K"); break;
    case 2: (void) strcat(format,"M"); break;
    case 3: (void) strcat(format,"G"); break;
    case 4: (void) strcat(format,"T"); break;
    case 5: (void) strcat(format,"P"); break;
    case 6: (void) strcat(format,"E"); break;
    }
}
