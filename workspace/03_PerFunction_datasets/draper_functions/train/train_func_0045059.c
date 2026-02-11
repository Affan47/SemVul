event_wait(NetEvWait*stmt)
{
      NetProc*tmp = stmt->statement();
      if (tmp)
	    return tmp->match_proc(this);
      else
	    return 0;
}
