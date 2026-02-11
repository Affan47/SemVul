getInputData(giopStream* g,omni::alignment_t align,size_t sz) {

  omni::ptr_arith_t last = omni::align_to((omni::ptr_arith_t)g->pd_inb_mkr,
					  align);

  omni::ptr_arith_t end = last + sz;

  if ( end <= (omni::ptr_arith_t) g->pd_inb_end) {
    return;
  }
  else {


    size_t extra = end - (omni::ptr_arith_t) g->pd_inb_end;
    if (extra != sz) {
      if (!g->inputFragmentToCome()) {


	sz = extra;
      }
      else {

	{
	  if( omniORB::trace(1) ) {
	    omniORB::logger l;
	    l << "Fatal error in unmarshalling message from "
	      << g->pd_strand->connection->peeraddress()
	      << ", invariant was violated at "
	      << __FILE__
	      << ":" << __LINE__ << '\n';
	  }
	}
	OMNIORB_ASSERT(0);

      }
    }
  }

  if (g->inputFragmentToCome() < sz) {
    if (!g->inputMatchedId()) {


      g->pd_strand->state(giopStrand::DYING);
    }
    OMNIORB_THROW(MARSHAL,MARSHAL_PassEndOfMessage,
		  (CORBA::CompletionStatus)g->completion());
  }

  if (g->inputMatchedId()) {
    if (g->pd_currentInputBuffer) {
      g->releaseInputBuffer(g->pd_currentInputBuffer);
      g->pd_currentInputBuffer = 0;
    }
    if (!g->pd_input) {
      g->pd_currentInputBuffer = g->inputChunk(g->inputFragmentToCome());
    }
    else {
      g->pd_currentInputBuffer = g->pd_input;
      g->pd_input = g->pd_currentInputBuffer->next;
      g->pd_currentInputBuffer->next = 0;
    }
  }
  else {

    giopStream_Buffer** pp = &g->pd_input;
    while (*pp) {
      pp = &((*pp)->next);
    }
    *pp = g->pd_currentInputBuffer;
    g->pd_currentInputBuffer = 0;
    g->pd_currentInputBuffer = g->inputChunk(g->inputFragmentToCome());
  }

  g->pd_inb_mkr = (void*)((omni::ptr_arith_t)g->pd_currentInputBuffer +
			  g->pd_currentInputBuffer->start);
  g->pd_inb_end = (void*)((omni::ptr_arith_t)g->pd_currentInputBuffer +
			  g->pd_currentInputBuffer->last);
  g->inputFragmentToCome(g->inputFragmentToCome() -
			 (g->pd_currentInputBuffer->last -
			  g->pd_currentInputBuffer->start));
}
