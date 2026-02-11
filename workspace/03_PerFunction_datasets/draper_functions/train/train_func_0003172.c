get_delegcontext(Arc::Message& msg) const {
  DelegationContext* deleg_ctx=NULL;
  Arc::MessageContextElement* mcontext = (*msg.Context())["deleg.context"];
  if(mcontext) {
    try {
      deleg_ctx = dynamic_cast<DelegationContext*>(mcontext);
    } catch(std::exception& e) { };
  };
  if(deleg_ctx) return deleg_ctx;
  deleg_ctx = new DelegationContext();
  if(deleg_ctx) {
    msg.Context()->Add("deleg.context",deleg_ctx);
  } else {
    logger.msg(Arc::ERROR, "Failed to acquire delegation context");
  }
  return deleg_ctx;
}
