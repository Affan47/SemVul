sge_sys_str2signal(const char *str)
{
   const sig_mapT *mapptr=sig_map;
   u_long32 signum;


   while (mapptr->sge_sig) {
      if (!strcasecmp(str, mapptr->signame)) {
         return mapptr->sig;
      }
      mapptr++;
   }


   if (sge_strisint(str)) {
      signum = strtol(str, NULL, 10);
      return signum;
   }

   return -1;
}
