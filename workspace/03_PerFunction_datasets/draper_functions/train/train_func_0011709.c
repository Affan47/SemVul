unmarshalWildCardRequestHeader(giopStream* g) {

  g->inputMatchedId(1);

  char* hdr = (char*)g->pd_currentInputBuffer +
                     g->pd_currentInputBuffer->start;

  ((GIOP_S*)g)->requestType((GIOP::MsgType)hdr[7]);
  switch (((GIOP_S*)g)->requestType()) {
  case GIOP::CloseConnection:
    inputRaiseCommFailure(g, "Orderly connection shutdown");
    break;
  case GIOP::Request:
  case GIOP::LocateRequest:
  case GIOP::CancelRequest:
    if (g->inputMessageSize() <= orbParameters::giopMaxMsgSize) {
      break;
    }
    inputTerminalProtocolError(g, __FILE__, __LINE__,
			       "GIOP message size limit exceeded");
    break;
  default:
    inputTerminalProtocolError(g, __FILE__, __LINE__,
			       "Unknown GIOP message type");

    break;
  }
}
