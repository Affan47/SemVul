DIMSE_printCFindStatusString(STD_NAMESPACE ostream& dumpStream, int status)
{
  dumpStream << "0x" << STD_NAMESPACE hex << STD_NAMESPACE setfill('0')
      << STD_NAMESPACE setw(4) << status;

  if ((status & 0xff00) == STATUS_FIND_Refused_OutOfResources)
  {
    dumpStream << ": Error: Refused - Out of resources";
  }
  else if ((status & 0xff00) == STATUS_FIND_Refused_SOPClassNotSupported)
  {
    dumpStream << ": Error: Refused - SOP Class not supported";
  }
  else if ((status & 0xff00) == STATUS_FIND_Failed_IdentifierDoesNotMatchSOPClass)
  {
    dumpStream << ": Error: Failed - Identifier does not match SOP Class";
  }
  else if ((status & 0xf000) == STATUS_FIND_Failed_UnableToProcess)
  {
    dumpStream << ": Error: Failed - Unable to process";
  }
  else if (status == STATUS_FIND_Cancel_MatchingTerminatedDueToCancelRequest)
  {
    dumpStream << ": Cancel: Matching terminated due to Cancel Request";
  }
  else if (status == STATUS_FIND_Pending_WarningUnsupportedOptionalKeys)
  {
    dumpStream << ": Pending: Warning - Unsupported optional keys";
  }
  else if (DICOM_WARNING_STATUS(status))
  {
    dumpStream << ": Warning";
  }
  else if (DICOM_PENDING_STATUS(status))
  {
    dumpStream << ": Pending";
  }
  else if (status == STATUS_Success)
  {
    dumpStream << ": Success";
  }
  else
  {
    dumpStream << ": Unknown Status Code";
  }
}
