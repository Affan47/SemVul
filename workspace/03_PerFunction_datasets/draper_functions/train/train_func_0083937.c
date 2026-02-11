OutFdReady()
{
   int Res;
   do
   {
      Res = write(OutFd,OutQueue.c_str(),OutQueue.length());
   }
   while (Res < 0 && errno == EINTR);

   if (Res <= 0)
      return MethodFailure();

   OutQueue.erase(0,Res);
   if (OutQueue.empty() == true)
      OutReady = false;

   return true;
}
