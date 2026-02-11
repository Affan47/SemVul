StopAssociation()
{
  ULConnection* mConnection = Internals->mConnection;

  BasePDU* thePDU = PDUFactory::ConstructReleasePDU();
  ULEvent theEvent(eARELEASERequest, thePDU);
  EStateID theState = RunEventLoop(theEvent, mConnection, NULL, false);

  return theState == eSta1Idle;
}
