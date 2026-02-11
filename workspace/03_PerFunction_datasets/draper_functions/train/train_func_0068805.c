vfs_configCpuDir(
  HOST_CFG *anchor,
  char *input,
  H_UINT *pArg)
{

   (void)pArg;
   if (strlen(input)> 3) {
      char  term[32];
      int   cpu;

      cpu = atoi(input+3);
      (void)snprintf(term, 32, "cpu%d", cpu);
      if (!strcmp(term, input))
         cfg_bitSet(&anchor->pCacheInfo, cpu);
      }
   return 0;
}
