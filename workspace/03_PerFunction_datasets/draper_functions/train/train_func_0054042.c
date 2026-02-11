getReserveSpace(giopStream* g,omni::alignment_t align,size_t sz) {


  if (outputHasReachedLimit(g)) {

    goto overflow;
  }

  g->pd_outb_mkr = (void*) omni::align_to((omni::ptr_arith_t)g->pd_outb_mkr,
					  align);

  if (sz == 0)
    return;

  if ((omni::ptr_arith_t)g->pd_outb_mkr < (omni::ptr_arith_t)g->pd_outb_end) {
    omni::ptr_arith_t newmkr = ((omni::ptr_arith_t)g->pd_outb_mkr + sz);
    if (newmkr <= (omni::ptr_arith_t)g->pd_outb_end)
      return;

    OMNIORB_ASSERT(0);
  }


  outputFlush(g);
  if (!outputHasReachedLimit(g))
    return;

 overflow:
    OMNIORB_THROW(MARSHAL,MARSHAL_MessageSizeExceedLimitOnClient,
		  (CORBA::CompletionStatus)g->completion());
}
