chsuser(uid,gid,hostname,ptrcode,permstr)
int uid;
int gid;
char *hostname ;
int *ptrcode ;
char *permstr;
{

   struct passwd *pw ;

   if ( chksuser(uid,gid,hostname,ptrcode,permstr) < 0 )
      return -2 ;
   if ( uid >=100 && ( (pw = getpwuid((uid_t)uid)) == NULL
#if defined(_WIN32)
      ))
#else
      || chsgroup(pw,gid)) )
#endif
   {
      *ptrcode = EACCES ;
      log(LOG_ERR,"chsuser(): user (%d,%d) does not exist at local host\n",uid,gid);
      return -2 ;
   }


   (void) setgroups(0, NULL);

   if ( (setgid((gid_t)gid)<0) || (setuid((uid_t)uid)<0) )  {
      *ptrcode = errno ;
      log(LOG_ERR,"chsuser(): unable to setuid,gid(%d,%d): %s, we are (uid=%d,gid=%d,euid=%d,egid=%d)\n",uid,gid,strerror(errno),(int) getuid(),(int) getgid(),(int) geteuid(),(int) getegid()) ;
      return -2 ;
   }
   return 0 ;
}
