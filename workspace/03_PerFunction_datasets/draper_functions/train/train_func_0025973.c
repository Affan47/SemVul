decrRefCount() {
  ASSERT_OMNI_TRACEDMUTEX_HELD(*omniTransportLock,0);

  omni_tracedmutex_lock sync(*omniTransportLock);
  pd_refcount--;
  OMNIORB_ASSERT(pd_refcount >=0);

  if (pd_refcount) return;


  if (RopeLink::is_empty(pd_strands) && !pd_nwaiting) {
    RopeLink::remove();
    delete this;
  }
  else {
    RopeLink* p = pd_strands.next;
    for (; p != &pd_strands; p = p->next) {
      giopStrand* g = (giopStrand*)p;
      if (g->state() != giopStrand::DYING) {
	g->state(giopStrand::TIMEDOUT);


	g->StrandList::remove();
	g->StrandList::insert(giopStrand::active_timedout);
      }
    }
  }
}
