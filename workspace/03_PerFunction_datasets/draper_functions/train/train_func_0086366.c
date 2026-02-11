xsh_free2Darray(double ** ccdtemp, int asize)
{
  int i;
  const int my_asize=asize;
  for (i=my_asize-1; i >=0; i--)
    {
     if (ccdtemp[i] !=NULL) cpl_free(ccdtemp[i]);
     else
       {
         printf("Error freeing memory at row= %d\n", i);
         return 1;
       }
    }
  if( ccdtemp !=NULL) cpl_free(ccdtemp);
  else
  {
   printf("Error freeing memory at the initial pointer");
   return 1;
  }
  return 0;
}
