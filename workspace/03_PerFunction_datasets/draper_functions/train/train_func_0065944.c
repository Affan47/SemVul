read(DcmItem &dset)
{
  OFCondition result = EC_Normal;
  DcmStack stack;
  OFString aString;

  READ_FROM_DATASET(DcmSignedLong, displayedAreaTopLeftHandCorner)
  READ_FROM_DATASET(DcmSignedLong, displayedAreaBottomRightHandCorner)
  READ_FROM_DATASET(DcmCodeString, presentationSizeMode)
  READ_FROM_DATASET(DcmDecimalString, presentationPixelSpacing)
  READ_FROM_DATASET(DcmIntegerString, presentationPixelAspectRatio)
  READ_FROM_DATASET(DcmFloatingPointSingle, presentationPixelMagnificationRatio)

  if (result==EC_Normal) result = referencedImageList.read(dset);


  if (displayedAreaTopLeftHandCorner.getLength() == 0)
  {
    result=EC_IllegalCall;
    DCMPSTAT_INFO("presentation state contains a display area selection SQ item with displayedAreaTopLeftHandCorner absent or empty");
  }
  else if (displayedAreaTopLeftHandCorner.getVM() != 2)
  {
    result=EC_IllegalCall;
    DCMPSTAT_INFO("presentation state contains a display area selection SQ item with displayedAreaTopLeftHandCorner VM != 2");
  }

  if (displayedAreaBottomRightHandCorner.getLength() == 0)
  {
    result=EC_IllegalCall;
    DCMPSTAT_INFO("presentation state contains a display area selection SQ item with displayedAreaBottomRightHandCorner absent or empty");
  }
  else if (displayedAreaBottomRightHandCorner.getVM() != 2)
  {
    result=EC_IllegalCall;
    DCMPSTAT_INFO("presentation state contains a display area selection SQ item with displayedAreaBottomRightHandCorner VM != 2");
  }

  if (presentationSizeMode.getLength() == 0)
  {
    result=EC_IllegalCall;
    DCMPSTAT_INFO("presentation state contains a display area selection SQ item with presentationSizeMode absent or empty");
  }
  else if (presentationSizeMode.getVM() != 1)
  {
    result=EC_IllegalCall;
    DCMPSTAT_INFO("presentation state contains a display area selection SQ item with presentationSizeMode VM != 1");
  } else {
    aString.clear();
    presentationSizeMode.getOFString(aString,0);
    if (aString=="TRUE SIZE")
    {
      if (presentationPixelSpacing.getVM() != 2)
      {
        result=EC_IllegalCall;
        DCMPSTAT_INFO("presentation state contains a display area selection SQ item with mode 'TRUE SIZE' but presentationPixelSpacing VM != 2");
      }
    } else if (aString == "MAGNIFY")
    {
      if (presentationPixelMagnificationRatio.getVM() != 1)
      {
        result=EC_IllegalCall;
        DCMPSTAT_INFO("presentation state contains a display area selection SQ item with mode 'MAGNIFY' but presentationPixelSpacing VM != 1");
      }
    } else if (aString != "SCALE TO FIT")
    {
      result=EC_IllegalCall;
      DCMPSTAT_INFO("presentation state contains a display area selection SQ item with unknown presentation size mode: " << aString);
    }
  }

  if ((presentationPixelSpacing.getLength() > 0)&&(presentationPixelSpacing.getVM() != 2))
  {
    result=EC_IllegalCall;
    DCMPSTAT_INFO("presentation state contains a display area selection SQ item with presentationPixelSpacing VM != 2");
}

  if ((presentationPixelAspectRatio.getLength() > 0)&&(presentationPixelAspectRatio.getVM() != 2))
  {
    result=EC_IllegalCall;
    DCMPSTAT_INFO("presentation state contains a display area selection SQ item with presentationPixelAspectRatio VM != 2");
  }

  if ((presentationPixelMagnificationRatio.getLength() > 0)&&(presentationPixelMagnificationRatio.getVM() != 1))
  {
    result=EC_IllegalCall;
    DCMPSTAT_INFO("presentation state contains a display area selection SQ item with presentationPixelMagnificationRatio VM != 1");
  }

  if ((presentationPixelSpacing.getLength() == 0)&&(presentationPixelAspectRatio.getVM() != 2))
  {
    result=EC_IllegalCall;
    DCMPSTAT_INFO("presentation state contains a display area selection SQ item with both presentationPixelSpacing and presentationPixelAspectRatio missing/incorrect");
  }

  return result;
}
