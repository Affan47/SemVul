ArgusPrintDstBytesLabel (char *buf)
{
   if (ArgusInput->ArgusManStart.ahdr.type & ARGUS_RMON) {
      if (Aflag)
         sprintf (&buf[strlen(buf)], "OutAppBytes ");
      else
      if (Rflag)
         sprintf (&buf[strlen(buf)], "OutBytes    ");
      else
         sprintf (&buf[strlen(buf)], "OutBytes    ");
   } else {
      if (Aflag)
         sprintf (&buf[strlen(buf)], "DAppBytes   ");
      else
      if (Rflag)
         sprintf (&buf[strlen(buf)], "SrcBytes    ");
      else
         sprintf (&buf[strlen(buf)], "DstBytes    ");
   }
}
