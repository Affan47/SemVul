copyOutputData(giopStream* g,void* b, size_t sz,
			   omni::alignment_t align) {

  if (outputHasReachedLimit(g)) {

    OMNIORB_THROW(MARSHAL,MARSHAL_MessageSizeExceedLimitOnClient,
		  (CORBA::CompletionStatus)g->completion());
  }

  omni::ptr_arith_t newmkr = omni::align_to((omni::ptr_arith_t)g->pd_outb_mkr,
					    align);
  OMNIORB_ASSERT(newmkr <= (omni::ptr_arith_t)g->pd_outb_end);

  g->pd_outb_mkr = (void*)newmkr;

  if (sz >= giopStream::directSendCutOff) {


    size_t leftover = (newmkr + sz) & 0x7;

    if (!g->outputFragmentSize()) {

      omni::ptr_arith_t outbuf_begin = ((omni::ptr_arith_t)
					g->pd_currentOutputBuffer +
					g->pd_currentOutputBuffer->start);

      CORBA::ULong fsz = (omni::ptr_arith_t) g->pd_outb_mkr -
            	         (omni::ptr_arith_t) outbuf_begin + sz - leftover - 12;

      *((CORBA::ULong*)((omni::ptr_arith_t)outbuf_begin + 8)) = fsz;
    }

    outputFlush(g,1);

    g->sendCopyChunk(b,sz - leftover);

    if (leftover) {
      if (outputHasReachedLimit(g)) {

	OMNIORB_THROW(MARSHAL,MARSHAL_MessageSizeExceedLimitOnClient,
		      (CORBA::CompletionStatus)g->completion());
      }
      b = (void*) ((omni::ptr_arith_t)b + sz - leftover);
    }
    sz = leftover;
  }

  while (sz) {
    size_t avail = (omni::ptr_arith_t) g->pd_outb_end	-
      (omni::ptr_arith_t) g->pd_outb_mkr;
    if (avail > sz) avail = sz;
    memcpy(g->pd_outb_mkr,b,avail);
    sz -= avail;
    g->pd_outb_mkr = (void*)((omni::ptr_arith_t) g->pd_outb_mkr + avail);
    b = (void*)((omni::ptr_arith_t) b + avail);
    if (g->pd_outb_mkr == g->pd_outb_end) {
      outputFlush(g);
      if (sz && outputHasReachedLimit(g)) {

	OMNIORB_THROW(MARSHAL,MARSHAL_MessageSizeExceedLimitOnClient,
		      (CORBA::CompletionStatus)g->completion());
      }
    }
  }
}
