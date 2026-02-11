psGetSysdata(void)
{
   psSys_t *sd;


   psRetrieveSystemData();

   if ((sd = (psSys_t *)malloc(sizeof(psSys_t))) == NULL) {
      return NULL;
   }
   memcpy(sd, &sysdata, sizeof(psSys_t));
   return sd;
}
