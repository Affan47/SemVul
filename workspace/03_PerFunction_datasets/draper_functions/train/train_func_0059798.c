evas_module_clean(void)
{
   static int call_count = 0;

   int noclean = -1;


   call_count++;
   if (call_count <= 256) return;
   call_count = 0;

   if (noclean == -1)
     {
	if (getenv("EVAS_NOCLEAN"))
          noclean = 1;
	else
          noclean = 0;
     }
   if (noclean == 1) return;


   return;


}
