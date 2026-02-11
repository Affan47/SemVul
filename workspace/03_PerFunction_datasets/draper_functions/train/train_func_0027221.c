write(DcmItem &dset)
{
  OFCondition result = EC_Normal;
  DcmElement *delem=NULL;
  DcmSequenceOfItems *dseq=NULL;
  DcmItem *ditem=NULL;

  if (useLUT)
  {
    ditem = new DcmItem();
    if (ditem)
    {
      dseq = new DcmSequenceOfItems(DCM_VOILUTSequence);
      if (dseq)
      {
        delem = new DcmUnsignedShort(voiLUTDescriptor);
        if (delem) ditem->insert(delem, OFTrue ); else result=EC_MemoryExhausted;
        delem = new DcmUnsignedShort(voiLUTData);
        if (delem) ditem->insert(delem, OFTrue ); else result=EC_MemoryExhausted;
        if (voiLUTExplanation.getLength() >0)
        {
          delem = new DcmLongString(voiLUTExplanation);
          if (delem) ditem->insert(delem, OFTrue ); else result=EC_MemoryExhausted;
        }
        if (result==EC_Normal)
        {
          dseq->insert(ditem);
          dset.insert(dseq, OFTrue );
        } else {

          delete dseq;
          delete ditem;
          result = EC_MemoryExhausted;
        }
      } else {

        delete ditem;
        result = EC_MemoryExhausted;
      }
    }
    else result = EC_MemoryExhausted;
  }
  else
  {
    ADD_TO_DATASET(DcmDecimalString, windowCenter)
    ADD_TO_DATASET(DcmDecimalString, windowWidth)
    if (windowCenterWidthExplanation.getLength() > 0) { ADD_TO_DATASET(DcmLongString, windowCenterWidthExplanation) }
  }

  if ((result == EC_Normal)&&(referencedImageList.size() >0)) result = referencedImageList.write(dset);
  return result;
}
