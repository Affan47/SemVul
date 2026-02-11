addPresentationLUTReference(DcmItem& dset)
{
  DcmElement *delem=NULL;
  OFCondition result = EC_Normal;

  ADD_TO_DATASET(DcmUnsignedShort, illumination)
  ADD_TO_DATASET(DcmUnsignedShort, reflectedAmbientLight)

  if (presentationLUTInstanceUID.size() > 0)
  {

    DcmUniqueIdentifier refsopclassuid(DCM_ReferencedSOPClassUID);
    DcmUniqueIdentifier refsopinstanceuid(DCM_ReferencedSOPInstanceUID);
    if (result==EC_Normal) result = refsopclassuid.putString(UID_PresentationLUTSOPClass);
    if (result==EC_Normal) result = refsopinstanceuid.putString(presentationLUTInstanceUID.c_str());
    DcmSequenceOfItems *dseq = new DcmSequenceOfItems(DCM_ReferencedPresentationLUTSequence);
    DcmItem *ditem = new DcmItem();
    if ((result == EC_Normal) && ditem && dseq)
    {
       ADD_TO_DATASET2(DcmUniqueIdentifier, refsopclassuid)
       ADD_TO_DATASET2(DcmUniqueIdentifier, refsopinstanceuid)
       if (result==EC_Normal)
       {
         dseq->insert(ditem);
         dset.insert(dseq, OFTrue );
       } else {
        delete dseq;
        delete ditem;
       }
    } else {
      delete dseq;
      delete ditem;
      result = EC_MemoryExhausted;
    }
  }
  return result;
}
