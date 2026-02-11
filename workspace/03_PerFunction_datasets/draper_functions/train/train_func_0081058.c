GetBetterConnection(int level,bool limit_reached)
{
   bool need_sleep=false;


   for(FA *fo=FirstSameSite(); fo!=0; fo=NextSameSite(fo))
   {
      Ftp *o=(Ftp*)fo;

      if(o->GetConnectLevel()!=CL_LOGGED_IN)
	 continue;
      if(!SameConnection(o))
	 continue;

      if(level==0 && xstrcmp(real_cwd,o->real_cwd))
	 continue;

      if(o->conn->data_sock!=-1 || o->state!=EOF_STATE || o->mode!=CLOSED)
      {

	 if(level<2)
	    continue;

	 if(!connection_takeover || (o->priority>=priority && !o->IsSuspended()))
	    continue;
	 if(o->conn->data_sock!=-1 && o->expect->Count()<=1)
	 {

	    if((o->flags&NOREST_MODE) && o->real_pos>0x1000)
	       continue;
	    if(o->QueryBool("web-mode",o->hostname))
	       continue;
	    o->DataAbort();
	    o->DataClose();
	    if(!o->conn)
	       return need_sleep;
	 }
	 else
	 {
	    if(!o->expect->IsEmpty() || o->disconnect_on_close)
	       continue;
	 }
      }
      else
      {
	 if(limit_reached)
	 {

	    int diff=o->last_priority-priority;
	    if(diff>0)
	    {

	       if(o->idle_timer.TimePassed()<diff)
	       {
		  TimeoutS(1);
		  need_sleep=true;
		  continue;
	       }
	    }
	 }
      }


      MoveConnectionHere(o);
      return false;
   }
   return need_sleep;
}
