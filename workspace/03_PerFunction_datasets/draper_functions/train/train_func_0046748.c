inputReplyBegin(giopStream* g,
			    void (*unmarshalHeader)(giopStream*)) {

  {
    omni_tracedmutex_lock sync(*omniTransportLock);

    if (!g->pd_strand->biDir) {

      while (!(g->inputFullyBuffered() || g->pd_rdlocked)) {
	if (!g->rdLockNonBlocking()) {
	  g->sleepOnRdLock();
	}
      }
    }
    else {


      while (!(g->pd_strand->state() == giopStrand::DYING ||
	       g->inputFullyBuffered() ) ) {
	OMNIORB_ASSERT(g->pd_rdlocked == 0);
	g->sleepOnRdLockAlways();
      }
      if (g->pd_strand->state() == giopStrand::DYING) {
	CORBA::ULong minor;
	CORBA::Boolean retry;
	g->notifyCommFailure(1,minor,retry);
	CORBA::CompletionStatus status;
	if (g->pd_strand->orderly_closed) {
	  status = CORBA::COMPLETED_NO;
	}
	else {
	  status = (CORBA::CompletionStatus)g->completion();
	}
	giopStream::CommFailure::_raise(minor,
					status,
					retry,
					__FILE__,__LINE__,
					"Connection closed while waiting for "
					"a reply on a bidirectional "
					"connection", g->pd_strand);

      }
    }
  }

  if (!g->pd_currentInputBuffer) {
  again:
    if (!g->pd_input) {
      giopStream_Buffer* p = g->inputMessage();
      inputQueueMessage(g,p);
      goto again;
    }
    else {
      g->pd_currentInputBuffer = g->pd_input;
      g->pd_input = g->pd_input->next;
      g->pd_currentInputBuffer->next = 0;
    }
  }

  char* hdr = (char*)g->pd_currentInputBuffer +
                     g->pd_currentInputBuffer->start;

  g->pd_unmarshal_byte_swap = (((hdr[6] & 0x1) == _OMNIORB_HOST_BYTE_ORDER_)
			       ? 0 : 1 );

  g->pd_inb_mkr = (void*)(hdr + 16);
  g->pd_inb_end = (void*)((omni::ptr_arith_t)g->pd_currentInputBuffer +
			  g->pd_currentInputBuffer->last);


  g->inputExpectAnotherFragment(((hdr[6] & 0x2) ? 1 : 0));
  g->inputMessageSize(g->pd_currentInputBuffer->size);
  g->inputFragmentToCome(g->pd_currentInputBuffer->size -
			 (g->pd_currentInputBuffer->last -
			  g->pd_currentInputBuffer->start));

  unmarshalHeader(g);

  if (g->inputMessageSize() > orbParameters::giopMaxMsgSize) {
    OMNIORB_THROW(MARSHAL,MARSHAL_MessageSizeExceedLimitOnClient,
		  CORBA::COMPLETED_YES);
  }
}
