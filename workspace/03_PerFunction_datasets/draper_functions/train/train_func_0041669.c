WSAFaultAssign(SOAPEnvelope& message,WSAFault fid) {

  SOAPFault& fault = *(message.Fault());
  if(&fault == NULL) return;
  NS ns;
  ns["wsa"]="http://www.w3.org/2005/08/addressing";
  message.Namespaces(ns);
  switch(fid) {
    case WSAFaultInvalidAddressingHeader:
    case WSAFaultInvalidAddress:
    case WSAFaultInvalidEPR:
    case WSAFaultInvalidCardinality:
    case WSAFaultMissingAddressInEPR:
    case WSAFaultDuplicateMessageID:
    case WSAFaultActionMismatch:
    case WSAFaultOnlyAnonymousAddressSupported:
    case WSAFaultOnlyNonAnonymousAddressSupported:
      fault.Code(SOAPFault::Sender);
      fault.Subcode(1,"wsa:InvalidAddressingHeader");
      fault.Reason(0,"A header representing a Message Addressing Property is not valid and the message cannot be processed");
      switch(fid) {
        case WSAFaultInvalidAddress:      fault.Subcode(2,"wsa:InvalidAddress"); break;
        case WSAFaultInvalidEPR:          fault.Subcode(2,"wsa:InvalidEPR"); break;
        case WSAFaultInvalidCardinality:  fault.Subcode(2,"wsa:InvalidCardinality"); break;
        case WSAFaultMissingAddressInEPR: fault.Subcode(2,"wsa:MissingAddressInEPR"); break;
        case WSAFaultDuplicateMessageID:  fault.Subcode(2,"wsa:DuplicateMessageID"); break;
        case WSAFaultActionMismatch:      fault.Subcode(2,"wsa:ActionMismatch"); break;
        case WSAFaultOnlyAnonymousAddressSupported: fault.Subcode(2,"wsa:OnlyAnonymousAddressSupported"); break;
        case WSAFaultOnlyNonAnonymousAddressSupported: fault.Subcode(2,"wsa:OnlyNonAnonymousAddressSupported"); break;
        default: break;
      };
    break;
    case WSAFaultMessageAddressingHeaderRequired:
      fault.Code(SOAPFault::Sender);
      fault.Subcode(1,"wsa:MessageAddressingHeaderRequired");
      fault.Reason(0,"A required header representing a Message Addressing Property is not present");
    break;
    case WSAFaultDestinationUnreachable:
      fault.Code(SOAPFault::Sender);
      fault.Subcode(1,"wsa:DestinationUnreachable");
      fault.Reason(0,"No route can be determined to reach [destination]");
    break;
    case WSAFaultActionNotSupported:
      fault.Code(SOAPFault::Sender);
      fault.Subcode(1,"wsa:ActionNotSupported");
      fault.Reason(0,"The [action] cannot be processed at the receiver");
    break;
    case WSAFaultEndpointUnavailable:
      fault.Code(SOAPFault::Receiver);
      fault.Subcode(1,"wsa:EndpointUnavailable");
      fault.Reason(0,"The endpoint is unable to process the message at this time");
    break;
    default: break;
  };
}
