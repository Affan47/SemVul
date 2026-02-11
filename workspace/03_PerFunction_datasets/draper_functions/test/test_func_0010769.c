OpGetTable()
{
   pmd_gettable_ot1 out ;
   int i ;

   for (i = 0, out.count = 0 ; i < TABLE_SIZE ; i++)
      if (table[i].used == USED)
	 out.count++ ;

   if (out.count > 0)
    {
       out.status = htons(SUCCESS) ;
       out.error = htons(PMD_ER_NOERROR) ;
    }
   else
    {
       out.status = htons(FAILURE) ;
       out.error = htons(PMD_ER_NOENTRY) ;
    }
   out.count = htons(out.count) ;
   if (!writen(newsock, (char *)&out, sizeof(out)))
      return ;

   if (ntohs(out.count) > 0)
      sendTable() ;
}
