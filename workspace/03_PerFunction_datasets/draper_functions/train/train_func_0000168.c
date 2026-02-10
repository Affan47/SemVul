OpUnmap()
{
  pmd_unmap_it in ;
  pmd_unmap_ot out ;

  if (!readn(newsock, (char *)&in, sizeof( pmd_unmap_it)))
     return ;

  if (ntohl(in.pid) > 0)
     out.count = unmapPid(ntohl(in.pid)) ;
  else
     out.count = unmapMapid(in.mapid, ntohs(in.protocol)) ;

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
  writen(newsock, (char *)&out, sizeof(pmd_unmap_ot)) ;
}
