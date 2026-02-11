addImageReference(
    DcmItem &dset,
    const char *aetitle,
    const char *filesetID,
    const char *filesetUID)
{
  DcmIntegerString numberOfFrames(DCM_NumberOfFrames);
  DcmUniqueIdentifier studyUID(DCM_StudyInstanceUID);
  DcmUniqueIdentifier seriesUID(DCM_SeriesInstanceUID);
  DcmUniqueIdentifier sopclassUID(DCM_SOPClassUID);
  DcmUniqueIdentifier imageUID(DCM_SOPInstanceUID);

  OFString ofstudyUID;
  OFString ofseriesUID;
  OFString ofsopclassUID;
  OFString ofimageUID;
  OFString aString;
  char buf[20];
  Sint32 i=0;
  Sint32 ofnumberOfFrames=0;
  DcmStack stack;

  READ_FROM_DATASET(DcmIntegerString, numberOfFrames)
  READ_FROM_DATASET(DcmUniqueIdentifier, studyUID)
  READ_FROM_DATASET(DcmUniqueIdentifier, seriesUID)
  READ_FROM_DATASET(DcmUniqueIdentifier, sopclassUID)
  READ_FROM_DATASET(DcmUniqueIdentifier, imageUID)

  numberOfFrames.getSint32(ofnumberOfFrames,0);
  seriesUID.getOFString(ofseriesUID,0);
  sopclassUID.getOFString(ofsopclassUID,0);
  imageUID.getOFString(ofimageUID,0);
  studyUID.getOFString(ofstudyUID,0);

  OFCondition result = EC_Normal;

  if (ofnumberOfFrames > 1)
  {
    for (i=0; i<ofnumberOfFrames; i++)
    {
        if (aString.length() > 0) sprintf(buf, "\\%ld", (long)(i+1)); else sprintf(buf, "%ld", (long)(i+1));
        aString += buf;
    }
    result = addImageReference(ofstudyUID.c_str(), ofseriesUID.c_str(), ofsopclassUID.c_str(),
      ofimageUID.c_str(), aString.c_str(), aetitle, filesetID, filesetUID);
  } else {
    result = addImageReference(ofstudyUID.c_str(), ofseriesUID.c_str(), ofsopclassUID.c_str(),
      ofimageUID.c_str(), NULL, aetitle, filesetID, filesetUID);
  }

  if (result == EC_Normal)
    createDefaultDisplayedArea(dset);

  return result;
}
