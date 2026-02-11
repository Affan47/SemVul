filmSessionNSet(T_DIMSE_Message& rq, DcmDataset *rqDataset, T_DIMSE_Message& rsp, DcmDataset *& rspDataset)
{
  if (filmSession && (filmSession->isInstance(rq.msg.NSetRQ.RequestedSOPInstanceUID)))
  {
    OFBool usePLUTinFilmSession = OFFalse;
    if (assoc && (0 != ASC_findAcceptedPresentationContextID(assoc, UID_PresentationLUTSOPClass)))
    {
      if (dviface.getTargetPrinterPresentationLUTinFilmSession(cfgname)) usePLUTinFilmSession = OFTrue;
    }

    DVPSFilmSession *newSession = new DVPSFilmSession(*filmSession);
    if (newSession)
    {
      if (newSession->printSCPSet(dviface, cfgname, rqDataset, rsp, rspDataset, usePLUTinFilmSession, presentationLUTList, storedPrintList))
      {
        delete filmSession;
        filmSession = newSession;
      } else delete newSession;
    } else {
      DCMPSTAT_INFO("cannot update film session, out of memory.");
      rsp.msg.NSetRSP.DimseStatus = STATUS_N_ProcessingFailure;
    }
  } else {

    DCMPSTAT_INFO("cannot update film session, object not found.");
    rsp.msg.NSetRSP.DimseStatus = STATUS_N_NoSuchObjectInstance;
  }
}
