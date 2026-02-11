delete_user(host, login)
char *host;
char *login;
{
   cid_deleteuser_it out ;
   cid_deleteuser_ot in ;
   u_short op ;
   int sd ;

   if ((sd = connectCid(host,login)) == -1)
      return 0 ;

   op = htons(CID_OP_DELETE_USER) ;
   strcpy(out.login, login) ;
   if (writen(sd, (char *)&op, sizeof(u_short)))
      if (writen(sd, (char *)&out, sizeof(cid_deleteuser_it)))
	 if (readn(sd, (char *)&in, sizeof(cid_deleteuser_ot)))
	    if (ntohs(in.status) == SUCCESS)
	     {
		close(sd) ;
		return 1 ;
	     }
   close(sd) ;
   return 0 ;
}
