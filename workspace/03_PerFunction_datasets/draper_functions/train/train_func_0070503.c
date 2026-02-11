freadjamindex(FILE *fp,s_JamIndex *s_JamIndex)
{
   uchar buf[SIZE_JAMINDEX];

   if(fread(buf,SIZE_JAMINDEX,1,fp) != 1)
      return 0;

   s_JamIndex->UserCRC   = jamgetulong(buf,JAMINDEX_USERCRC);
   s_JamIndex->HdrOffset = jamgetulong(buf,JAMINDEX_HDROFFSET);

   return 1;
}
