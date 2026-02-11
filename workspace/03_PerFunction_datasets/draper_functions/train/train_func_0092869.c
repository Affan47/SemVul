RestCheck(int act)
{
   if(is2XX(act) || is3XX(act))
   {
      real_pos=conn->rest_pos;
      conn->last_rest=conn->rest_pos;
      return;
   }
   real_pos=0;
   if(pos==0)
      return;
   if(is5XX(act))
   {
      if(cmd_unsupported(act))
	 conn->rest_supported=false;
      LogNote(2,_("Switching to NOREST mode"));
      flags|=NOREST_MODE;
      if(mode==STORE)
	 pos=0;
      if(copy_mode!=COPY_NONE)
	 copy_failed=true;
      return;
   }
   Disconnect();
}
