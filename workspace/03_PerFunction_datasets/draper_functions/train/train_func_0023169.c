OpGetFulltable()
{
   cid_getfulltable_ot1 out ;
   int i ;

   for (i = 0, out.count = 0 ; i < TABLE_SIZE ; i++)
      if (table[i].used == USED)
         out.count++ ;

   if (out.count > 0)
    {
       out.status = htons(SUCCESS) ;
       out.error = htons(CID_ER_NOERROR) ;
    }
   else
    {
       out.status = htons(FAILURE) ;
       out.error = htons(CID_ER_NOENTRY) ;
    }

   out.count = htons(out.count) ;
   if (!writen(newsock, (char *)&out, sizeof(cid_getfulltable_ot1)))
      return ;
   if (ntohs(out.count) > 0)
      sendFulltable() ;
}
