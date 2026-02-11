del_trigger(void (* callback)(void *), void * cl_data)
{
   DEBUG_MSG("DataPool::del_trigger(): func=" << (void *) callback << "\n");
   DEBUG_MAKE_INDENT(3);

   for(;;)
   {
      GP<Trigger> trigger;
      {
	 GCriticalSectionLock lock(&triggers_lock);
	 for(GPosition pos=triggers_list;pos;)
	 {
	    GP<Trigger> t=triggers_list[pos];
	    if (t->callback==callback && t->cl_data==cl_data)
	    {
	       trigger=t;
	       GPosition this_pos=pos;
	       ++pos;
	       triggers_list.del(this_pos);
	       break;
	    } else
              ++pos;
	 }
      }


      if (trigger)
        trigger->disabled=1;
      else
        break;
   }

   GP<DataPool> pool = this->pool;
   if (pool)
     pool->del_trigger(callback, cl_data);
}
