read(DcmItem &dset)
{
  OFCondition result = EC_Normal;
  DcmStack stack;
  DcmSequenceOfItems *seq;
  DcmItem *item;

  READ_FROM_DATASET(DcmDecimalString, windowCenter)
  READ_FROM_DATASET(DcmDecimalString, windowWidth)
  READ_FROM_DATASET(DcmLongString, windowCenterWidthExplanation)


  if (result==EC_Normal)
  {
    stack.clear();
    if (EC_Normal == dset.search(DCM_VOILUTSequence, stack, ESM_fromHere, OFFalse))
    {
      seq=(DcmSequenceOfItems *)stack.top();
      if (seq->card() ==1)
      {
         item = seq->getItem(0);
         stack.clear();
         if (EC_Normal == item->search((DcmTagKey &)voiLUTDescriptor.getTag(),
           stack, ESM_fromHere, OFFalse))
         {
           voiLUTDescriptor = *((DcmUnsignedShort *)(stack.top()));
         }
         stack.clear();
         if (EC_Normal == item->search((DcmTagKey &)voiLUTExplanation.getTag(),
           stack, ESM_fromHere, OFFalse))
         {
           voiLUTExplanation = *((DcmLongString *)(stack.top()));
         }
         stack.clear();
         if (EC_Normal == item->search((DcmTagKey &)voiLUTData.getTag(),
           stack, ESM_fromHere, OFFalse))
         {
           voiLUTData = *((DcmUnsignedShort *)(stack.top()));
         }
      } else {
        result=EC_TagNotFound;
        DCMPSTAT_INFO("VOI LUT SQ does not have exactly one item in presentation state");
      }
    }
  }

  if (result==EC_Normal) result = referencedImageList.read(dset);


  if (result==EC_Normal)
  {
    if (windowCenter.getLength() > 0)
    {
      useLUT = OFFalse;

      if (windowWidth.getLength() == 0)
      {
        result=EC_IllegalCall;
        DCMPSTAT_INFO("windowCenter present but windowWidth absent or empty in presentation state");
      }
      else if (windowWidth.getVM() != 1)
      {
        result=EC_IllegalCall;
        DCMPSTAT_INFO("windowCenter present but windowWidth VM != 1 in presentation state");
      }
      if (windowCenter.getVM() != 1)
      {
        result=EC_IllegalCall;
        DCMPSTAT_INFO("windowCenter present but VM != 1 in presentation state");
      }
    } else useLUT = OFTrue;

    if (voiLUTData.getLength() > 0)
    {

      if (! useLUT)
      {
        result=EC_IllegalCall;
        DCMPSTAT_INFO("both VOI window and LUT present in presentation state");
      }

      if (voiLUTDescriptor.getLength() == 0)
      {
        result=EC_IllegalCall;
        DCMPSTAT_INFO("voiLUTData present but voiLUTDescriptor absent or empty in presentation state");
      }
      else if (voiLUTDescriptor.getVM() != 3)
      {
        result=EC_IllegalCall;
        DCMPSTAT_INFO("voiLUTData present but voiLUTDescriptor VM != 3 in presentation state");
      }
    }
    else if (useLUT)
    {
        result=EC_IllegalCall;
        DCMPSTAT_INFO("neither VOI window nor LUT present in presentation state");
    }
  }
  return result;
}
