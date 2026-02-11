outputRemaining(const giopStream* g) {
  CORBA::ULong total = g->outputMessageSize();
  if (!total) {
    return orbParameters::giopMaxMsgSize - currentOutputPtr(g);
  }
  else {
    return total - currentOutputPtr(g);
  }
}
