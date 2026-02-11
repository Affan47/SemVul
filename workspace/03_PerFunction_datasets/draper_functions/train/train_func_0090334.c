DetermineEventByPDU(const BasePDU* inPDU)
{
  if(inPDU)
    {
    const AAssociateRQPDU* theAAssociateRQPDU = dynamic_cast<const AAssociateRQPDU*>(inPDU);
    if (theAAssociateRQPDU != NULL)
      {
      return eAASSOCIATE_RQPDUreceived;
      }
    const AAssociateACPDU* theAAssociateACPDU = dynamic_cast<const AAssociateACPDU*>(inPDU);
    if (theAAssociateACPDU != NULL)
      {
      return eASSOCIATE_ACPDUreceived;
      }
    const AAssociateRJPDU* theAAssociateRJPDU = dynamic_cast<const AAssociateRJPDU*>(inPDU);
    if (theAAssociateRJPDU != NULL)
      {
      return eASSOCIATE_RJPDUreceived;
      }
    const PDataTFPDU* thePDataTFPDU = dynamic_cast<const PDataTFPDU*>(inPDU);
    if (thePDataTFPDU != NULL)
      {

      const PresentationDataValue &pdv = thePDataTFPDU->GetPresentationDataValue(0);
      (void)pdv;
#if 0
      int mh = pdv.GetMessageHeader();
      if( mh == 3 )
        {


        std::cout << "This was the last fragment of the message data set" << std::endl;
        }
#endif
      return ePDATATFPDU;
      }
    const AReleaseRQPDU* theAReleaseRQPDU = dynamic_cast<const AReleaseRQPDU*>(inPDU);
    if (theAReleaseRQPDU != NULL)
      {
      return eARELEASE_RQPDUReceivedOpen;
      }
    const AReleaseRPPDU* theAReleaseRPPDU = dynamic_cast<const AReleaseRPPDU*>(inPDU);
    if (theAReleaseRPPDU != NULL)
      {
      return eARELEASE_RPPDUReceived;
      }
    const AAbortPDU* theAAbortPDU = dynamic_cast<const AAbortPDU*>(inPDU);
    if (theAAbortPDU != NULL)
      {
      return eAABORTPDUReceivedOpen;
      }
    }
  return eEventDoesNotExist;
}
