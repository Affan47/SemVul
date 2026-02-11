check_triggers(void)

{
  DEBUG_MSG("DataPool::check_triggers(): calling activated trigger callbacks.\n");
  DEBUG_MAKE_INDENT(3);

  if (!pool && !furl.is_local_file_url())
    while(true)
      {
	GP<Trigger> trigger;


	{
	  GCriticalSectionLock list_lock(&triggers_lock);
	  for(GPosition pos=triggers_list;pos;++pos)
	    {
	      GP<Trigger> t=triggers_list[pos];
	      if (is_eof()
		  || (t->length>=0 &&
		      block_list->get_bytes(t->start, t->length)==t->length))
		{
		  trigger=t;
		  break;
		}
	    }
	}

	if (trigger)
	  {


	    {
	      GMonitorLock lock(&trigger->disabled);
	      if (!trigger->disabled)
		call_callback(trigger->callback, trigger->cl_data);
	    }


	    GCriticalSectionLock list_lock(&triggers_lock);
	    for(GPosition pos=triggers_list;pos;++pos)
	      if (triggers_list[pos]==trigger)
		{
		  triggers_list.del(pos);
		  break;
		}
	  } else break;
      }
}
