ChildSigHandler(int Signal)
{
   int Status;
   int Pid;

   int ErrnoSave = errno;

   SigChilds++;

   for(; ; ) {

      if((Pid = waitpid(-1,&Status,WNOHANG)) == -1 || Pid == 0) {
         break;
      }

      ChildExits++;
      if(((ExitStatWr + 1) % MAX_CHILDREN) == ExitStatRd) {

         bExitStatRingOvfl = TRUE;
         ExitStatRingOvfls++;
      }
      else {
         ChildExitStatus[ExitStatWr].ExitStatus = Status;
         ChildExitStatus[ExitStatWr].Pid = Pid;
         ExitStatWr = (ExitStatWr + 1) % MAX_CHILDREN;
      }
   }
   errno = ErrnoSave;
}
