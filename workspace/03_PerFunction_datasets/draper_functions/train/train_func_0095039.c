newInstance(
  DcmItem *dataset,
  const char *purposeOfReferenceCodingScheme,
  const char *purposeOfReferenceCodeValue,
  const char *purposeOfReferenceCodeMeaning)
{
  if (dataset == NULL) return EC_IllegalCall;
  OFCondition result = EC_Normal;


  const char *classUID = NULL;
  const char *instanceUID = NULL;


  OFCondition tempResult = dataset->findAndGetString(DCM_SOPClassUID, classUID);
  if (tempResult.good()) tempResult = dataset->findAndGetString(DCM_SOPInstanceUID, instanceUID);
  if (tempResult.good() && classUID && instanceUID)
  {

    DcmSequenceOfItems *dseq = new DcmSequenceOfItems(DCM_SourceImageSequence);
    if (dseq)
    {
      DcmItem *ditem = new DcmItem();
      if (ditem)
      {
        dseq->insert(ditem);
        DcmElement *elem1 = new DcmUniqueIdentifier(DCM_ReferencedSOPClassUID);
        if (elem1)
        {
          result = elem1->putString(classUID);
          ditem->insert(elem1, OFTrue );
          if (result.good())
          {
            DcmElement *elem2 = new DcmUniqueIdentifier(DCM_ReferencedSOPInstanceUID);
            if (elem2)
            {
              result = elem2->putString(instanceUID);
              ditem->insert(elem2, OFTrue );
            } else result = EC_MemoryExhausted;
          }
        } else result = EC_MemoryExhausted;

        if (result.good() && purposeOfReferenceCodingScheme &&
           purposeOfReferenceCodeValue && purposeOfReferenceCodeMeaning)
        {

          result = DcmCodec::insertCodeSequence(ditem, DCM_PurposeOfReferenceCodeSequence,
            purposeOfReferenceCodingScheme, purposeOfReferenceCodeValue, purposeOfReferenceCodeMeaning);
        }
      } else result = EC_MemoryExhausted;
      if (result.good()) dataset->insert(dseq, OFTrue); else delete dseq;
    } else result = EC_MemoryExhausted;
  }


  if (result.good())
  {
    char new_uid[100];
    DcmElement *elem = new DcmUniqueIdentifier(DCM_SOPInstanceUID);
    if (elem)
    {
      if (EC_Normal == (result = elem->putString(dcmGenerateUniqueIdentifier(new_uid))))
        dataset->insert(elem, OFTrue);
        else delete elem;
    } else result = EC_MemoryExhausted;
  }

  return result;
}
