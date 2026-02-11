change_param(const String &in_s, Element *e, void *vparam,
			  ErrorHandler *errh)
{
  RatedSource *rs = (RatedSource *)e;
  String s = cp_uncomment(in_s);
  switch ((intptr_t)vparam) {

  case 0:
      rs->_data = in_s;
      if (rs->_packet)
	  rs->_packet->kill();
      rs->_packet = Packet::make(rs->_data.data(), rs->_data.length());
      break;

   case 1: {
     unsigned rate;
     if (!cp_integer(s, &rate))
       return errh->error("rate parameter must be integer >= 0");
     if (rate > GapRate::MAX_RATE)

       return errh->error("rate too large; max is %u", GapRate::MAX_RATE);
     rs->_rate.set_rate(rate);
     break;
   }

   case 2: {
     int limit;
     if (!cp_integer(s, &limit))
       return errh->error("limit parameter must be integer");
     rs->_limit = (limit < 0 ? NO_LIMIT : limit);
     break;
   }

   case 3: {
     bool active;
     if (!cp_bool(s, &active))
       return errh->error("active parameter must be boolean");
     rs->_active = active;
     if (rs->output_is_push(0) && !rs->_task.scheduled() && active) {
       rs->_rate.reset();
       rs->_task.reschedule();
     }
     break;
   }

   case 5: {
     rs->_count = 0;
     rs->_rate.reset();
     if (rs->output_is_push(0) && !rs->_task.scheduled() && rs->_active)
       rs->_task.reschedule();
     break;
   }

   case 6: {
     int datasize;
     if (!cp_integer(s, &datasize) || datasize < 1)
       return errh->error("datasize parameter must be integer >= 1");
     rs->_datasize = datasize;
     rs->setup_packet();
     break;
   }
  }
  return 0;
}
