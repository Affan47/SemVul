GetCurStat()
{
   memset(&CurStat,0,sizeof(CurStat));

	if (DBLoaded)
	{


   InitQuery("st");

   Data.data = &CurStat;
   Data.ulen = sizeof(CurStat);
   Data.flags = DB_DBT_USERMEM;
		if (Get() == false)
      {
	 CurStat.Flags = 0;
      }
		CurStat.Flags = ntohl(CurStat.Flags);
		CurStat.FileSize = ntohl(CurStat.FileSize);
   }
	return true;
}
