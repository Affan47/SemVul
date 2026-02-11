addImageBox(
  const char *instanceuid,
  const char *retrieveaetitle,
  const char *refstudyuid,
  const char *refseriesuid,
  const char *refsopclassuid,
  const char *refsopinstanceuid,
  const char *requestedimagesize,
  const char *patientid,
  const char *presentationlutuid)
{
  OFCondition result = EC_Normal;
  DVPSImageBoxContent *newImage = new DVPSImageBoxContent();
  if (newImage)
  {
    result = newImage->setContent(instanceuid, retrieveaetitle, refstudyuid,
               refseriesuid, refsopclassuid, refsopinstanceuid,
               requestedimagesize, patientid, presentationlutuid);
    if (EC_Normal == result) list_.push_back(newImage); else delete newImage;
  } else result = EC_MemoryExhausted;
  return result;
}
