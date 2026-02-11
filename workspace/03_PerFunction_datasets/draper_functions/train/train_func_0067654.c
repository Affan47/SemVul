Do()
{
   int m=STALL;
   if(done)
      return m;
   if(waiting_num<1)
   {
      NextFile();
      if(waiting_num==0)
      {
	 done=true;
	 m=MOVED;
      }
      else if(cp==0)
	 cp=(CopyJob*)waiting[0];
   }
   CopyJob *j=(CopyJob*)FindDoneAwaitedJob();
   if(j==0)
      return m;
   RemoveWaiting(j);
   if(j->ExitCode()!=0)
      errors++;
   count++;
   bytes+=j->GetBytesCount();
   time_spent+=j->GetTimeSpent();
   Delete(j);
   if(cp==j)
      cp=0;
   if(waiting_num>0 && cp==0)
      cp=(CopyJob*)waiting[0];
   return MOVED;
}
