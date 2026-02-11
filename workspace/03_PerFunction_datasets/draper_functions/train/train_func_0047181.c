Xen_Domain(void)

{
FILE *fp;
char buffer[CF_BUFSIZE];
int sufficient = 0;

CfOut(cf_verbose,"","This appears to be a xen pv system.\n");
NewClass("xen");


if ((fp = fopen("/proc/xen/capabilities","r")) != NULL)
   {
   while (!feof(fp))
      {
      CfReadLine(buffer,CF_BUFSIZE,fp);
      if (strstr(buffer,"control_d"))
         {
         NewClass("xen_dom0");
         sufficient = 1;
         }
      }

   if (!sufficient)
      {
      NewClass("xen_domu_pv");
      sufficient = 1;
      }

   fclose(fp);
   }

return sufficient < 1 ? 1 : 0;
}
