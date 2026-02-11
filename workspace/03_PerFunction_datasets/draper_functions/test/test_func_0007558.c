outputFlush(giopStream* g) {

  omni::ptr_arith_t outbuf_begin = ((omni::ptr_arith_t)
				    g->pd_currentOutputBuffer +
				    g->pd_currentOutputBuffer->start);

  CORBA::ULong fsz =   (omni::ptr_arith_t) g->pd_outb_mkr - outbuf_begin;

  if (!g->outputMessageSize()) {

    char* hdr = (char*)outbuf_begin;

    CORBA::ULong msgsz = *((CORBA::ULong*)(hdr + 8));


    if (hdr[7] == (char) GIOP::Request) {

      GIOP_C& giop_c = *(GIOP_C*)g;

      cdrCountingStream cs(g->TCS_C(),g->TCS_W(),msgsz);

      giop_c.calldescriptor()->marshalArguments(cs);

      msgsz = cs.total() - 12;
    }
    else if (hdr[7] == (char) GIOP::Reply) {

      GIOP_S& giop_s = *(GIOP_S*)g;

      cdrCountingStream cs(g->TCS_C(),g->TCS_W(),msgsz);

      giop_s.calldescriptor()->marshalReturnedValues(cs);

      msgsz = cs.total() - 12;
    }
    else {

      if( omniORB::trace(1) ) {
	omniORB::logger l;
	l << "Fatal error in sending message to "
	  << g->pd_strand->connection->peeraddress()
	  << ", invariant was violated at "
	  << __FILE__
	  << ":" << __LINE__ << '\n';
      }
      OMNIORB_ASSERT(0);

    }
    *((CORBA::ULong*)(hdr + 8)) = msgsz;
    outputSetMessageSize(g,msgsz);
  }
  if (g->outputFragmentSize()) {
    g->outputFragmentSize(g->outputFragmentSize()+fsz);
  }
  else {
    g->outputFragmentSize(fsz - 12);
  }
  g->pd_currentOutputBuffer->last = g->pd_currentOutputBuffer->start + fsz;
  g->sendChunk(g->pd_currentOutputBuffer);

  if (outbuf_begin & 0x7) {

    g->pd_currentOutputBuffer->alignStart(omni::ALIGN_8);
    outbuf_begin = ((omni::ptr_arith_t) g->pd_currentOutputBuffer +
		                        g->pd_currentOutputBuffer->start);
  }

  g->pd_outb_mkr = (void*) outbuf_begin;
  g->pd_outb_end = (void*)((omni::ptr_arith_t)g->pd_currentOutputBuffer +
			   g->pd_currentOutputBuffer->end);
  g->pd_currentOutputBuffer->last = g->pd_currentOutputBuffer->start;
}
