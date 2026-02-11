OpKill()
{
   cid_kill_it in ;
   cid_kill_ot out ;
   int i ;

   if (!readn(newsock, (char *)&in, sizeof(cid_kill_it)))
      return ;

   for (i = 0 ; i < TABLE_SIZE ; i++)
      if ((table[i].used == USED) && (!strcmp(in.appid, table[i].appid))
          && (!strcmp(in.name, table[i].name)))
       {
          kill(table[i].pid, SIGTERM) ;
          ungetSlot(i) ;
          out.status = htons(SUCCESS) ;  out.error = htons(CID_ER_NOERROR) ;
          writen(newsock, (char *)&out, sizeof(cid_kill_ot)) ;
          return ;
       }

   out.status = htons(FAILURE) ;  out.error = htons(CID_ER_NOENTRY) ;
   writen(newsock, (char *)&out, sizeof(cid_kill_ot)) ;
}
