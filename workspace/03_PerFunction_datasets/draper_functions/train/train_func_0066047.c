printSCPDelete(T_DIMSE_Message& rq, T_DIMSE_Message& rsp)
{
  OFListIterator(DVPSPresentationLUT *) first = list_.begin();
  OFListIterator(DVPSPresentationLUT *) last = list_.end();
  OFBool found = OFFalse;
  OFString theUID(rq.msg.NDeleteRQ.RequestedSOPInstanceUID);
  while ((first != last) && (!found))
  {
    if (theUID == (*first)->getSOPInstanceUID()) found = OFTrue;
    else ++first;
  }

  if (found)
  {
    delete (*first);
    list_.erase(first);
  } else {

    DCMPSTAT_INFO("cannot delete presentation LUT with instance UID '" << rq.msg.NDeleteRQ.RequestedSOPInstanceUID << "': object does not exist.");
    rsp.msg.NDeleteRSP.DimseStatus = STATUS_N_NoSuchObjectInstance;
  }
}
