printSCPCreate(
  unsigned long numBoxes,
  DcmUniqueIdentifier& studyUID,
  DcmUniqueIdentifier& seriesUID,
  const char *aetitle)
{
  clear();
  DVPSImageBoxContent *box = NULL;
  char uid[100];
  for (unsigned long i=0; i<numBoxes; i++)
  {
    box = new DVPSImageBoxContent();
    if (box)
    {
      if ((EC_Normal == box->setSOPInstanceUID(dcmGenerateUniqueIdentifier(uid))) &&
          (EC_Normal == box->setUIDsAndAETitle(studyUID, seriesUID, aetitle)))
      {
        list_.push_back(box);
      }
      else
      {
      	delete box;
      	return OFFalse;
      }
    } else return OFFalse;
  }
  return OFTrue;
}
