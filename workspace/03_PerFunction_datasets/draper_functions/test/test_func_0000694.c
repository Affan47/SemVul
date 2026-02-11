DoInstallPostFork(int statusFd)
{
   bool goResult = Go(statusFd);
   if(goResult == false)
      return Failed;

   return Res;
}
