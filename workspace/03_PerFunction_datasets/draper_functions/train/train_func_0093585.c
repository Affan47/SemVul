verifyHandler(p_h)
handler_t *p_h;
{
   cid_verifyhandler_it out ;
   cid_verifyhandler_ot in ;
   u_short op ;
   int sd ;

   op = htons(CID_OP_VERIFY_HANDLER) ;
   if ((sd = get_socket()) == -1)
      return 0 ;
   strcpy(out.login, p_h->login) ;
   strcpy(out.rlogin, login) ;
   out.type = p_h->type == FAH ? htons(CID_TYPE_FAH) : htons(CID_TYPE_TSH) ;

   sprintf(mapid,"sng$cid$%s",p_h->login);
   if (!(cidport=pmd_getmap(mapid,p_h->host,(u_short)PMD_PROT_TCP)))
   {
        printf("Remote host lookup failure. \n");
        return 0;
   }
   if (do_connect(sd, p_h->host, cidport))
      if (writen(sd, (char *)&op, sizeof(u_short)))
	 if (writen(sd, (char *)&out, sizeof(cid_verifyhandler_it)))
	    if (readn(sd, (char *)&in, sizeof(cid_verifyhandler_ot)))
	       if (ntohs(in.status) == SUCCESS)
		{
		   close(sd) ;
		   return 1 ;
		}
   close(sd) ;
   return 0 ;
}
