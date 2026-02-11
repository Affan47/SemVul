init_ptt(void)
{
   pttfd = open (ptt_path, O_RDWR);
   if (pttfd>0)
   {
      if (ctl_ptt(0)<0)
         return -1;
   }
   return pttfd;
}
