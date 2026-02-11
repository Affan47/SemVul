OpFseek()
{
   fah_fseek_it in ;
   fah_fseek_ot out ;
   u_short fid ;

   if (!readn(newsock, (char *)&in, sizeof(in)))
      return ;
   fid = ntohs(in.fid) ;

   if (!(fid < TABLE_SIZE && table[fid].fp != NULL))
    {
       out.status = htons(FAILURE) ;
       out.error = htons(FAH_ER_NOTOPEN) ;
    }
   else
      if (fseek(table[fid].fp, ntohl(in.offset), ntohl(in.from)) == -1)
       {
	  out.status = htons(FAILURE) ;
	  out.error = htons(FAH_ER_FSEEK) ;
       }
      else
       {
	  out.status = htons(SUCCESS) ;
	  out.error = htons(FAH_ER_NOERROR) ;
       }
   writen(newsock, (char *)&out, sizeof(out)) ;
}
