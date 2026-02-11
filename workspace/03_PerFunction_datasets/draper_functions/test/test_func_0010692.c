Kill(int sig)
{
   Do();
   if(status!=RUNNING)
      return -1;

   int res;
   res=kill(-pid,sig);
   if(res==-1)
      res=kill(pid,sig);
   return res;
}
