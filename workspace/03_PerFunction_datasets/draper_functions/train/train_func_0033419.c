pm_strcpy(POOL_MEM &pm, const char *str)
{
   int len;

   if (!str) str = "";

   len = strlen(str) + 1;
   pm.check_size(len);
   memcpy(pm.c_str(), str, len);
   return len - 1;
}
