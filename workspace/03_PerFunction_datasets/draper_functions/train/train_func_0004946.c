SetDateTime(struct tm *ptm)
{

   if(local_time)
   	 Ht_t = mktime(ptm);
   else
   	 Ht_t = HtTimeGM(ptm);

}
