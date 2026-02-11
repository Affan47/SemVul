inputRemaining(giopStream* g) {

  if (g->inputExpectAnotherFragment()) {
    return orbParameters::giopMaxMsgSize - currentInputPtr(g);
  }
  else {
    return (g->inputFragmentToCome() + ((omni::ptr_arith_t)g->pd_inb_end -
					(omni::ptr_arith_t)g->pd_inb_mkr));
  }
}
