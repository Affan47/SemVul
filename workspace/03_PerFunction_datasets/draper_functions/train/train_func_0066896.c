file_remove(host, login, path)
char *host;
char *login;
char *path;
{
   cid_remove_ot in ;
   cid_remove_it out ;
   struct passwd *p_passwd ;
   u_short op ;
   int sd ;

   if ((sd = connectCid(host,login)) == -1)
      return 0 ;

   strcpy(out.login, login) ;
   p_passwd = getpwuid(getuid()) ;
   strcpy(out.rlogin, p_passwd->pw_name) ;
   strcpy(out.path, path) ;
   op = htons(CID_OP_REMOVE) ;

   if (writen(sd, (char *)&op, sizeof(u_short)))
      if (writen(sd, (char *)&out, sizeof(cid_remove_it)))
	 if (readn(sd, (char *)&in, sizeof(cid_remove_ot)))
	    if (ntohs(in.status) == SUCCESS)
	     {
		close(sd) ;
		return 1 ;
	     }
   close(sd) ;
   return 0 ;
}
