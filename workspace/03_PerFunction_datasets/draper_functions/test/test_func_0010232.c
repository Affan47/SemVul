ArgusPrintSrcTTLLabel (char *buf)
{
   if (RaPrintDistance)
      sprintf (&buf[strlen(buf)], "SrcDis ");
   else
      sprintf (&buf[strlen(buf)], "SrcTTL ");
}
