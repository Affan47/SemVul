PerformAction(Subject *, ULEvent& inEvent, ULConnection& inConnection,
        bool& outWaitingForEvent, EEventID& outRaisedEvent){


  assert(!inEvent.GetPDUs().empty());
  AAssociateACPDU* acpdu;
    acpdu = dynamic_cast<AAssociateACPDU*>(inEvent.GetPDUs()[0]);
  assert( acpdu );
  uint32_t maxpdu = acpdu->GetUserInformation().GetMaximumLengthSub().GetMaximumLength();
  inConnection.SetMaxPDUSize(maxpdu);


  for( unsigned int index = 0; index < acpdu->GetNumberOfPresentationContextAC(); index++ ){
    PresentationContextAC const &pc = acpdu->GetPresentationContextAC(index);
    inConnection.AddAcceptedPresentationContext(pc);
  }

  outWaitingForEvent = false;
  outRaisedEvent = eEventDoesNotExist;

  return eSta6TransferReady;
}
