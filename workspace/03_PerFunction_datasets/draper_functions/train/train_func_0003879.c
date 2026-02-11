createDefaultDisplayedArea(DcmItem &dset)
{
  DcmUnsignedShort rows(DCM_Rows);
  DcmUnsignedShort columns(DCM_Columns);
  DcmUniqueIdentifier sopclassUID(DCM_SOPClassUID);
  DcmUniqueIdentifier imageUID(DCM_SOPInstanceUID);
  DcmDecimalString imagerPixelSpacing(DCM_ImagerPixelSpacing);
  DcmDecimalString pixelSpacing(DCM_PixelSpacing);
  DcmIntegerString pixelAspectRatio(DCM_PixelAspectRatio);
  Uint16 cols_uint=0;
  Uint16 rows_uint=0;
  char *c_sopclassUID = NULL;
  char *c_imageUID = NULL;
  char *pixelspacing = NULL;
  OFCondition result = EC_Normal;
  DcmStack stack;

  READ_FROM_DATASET(DcmUnsignedShort, rows)
  READ_FROM_DATASET(DcmUnsignedShort, columns)
  READ_FROM_DATASET(DcmUniqueIdentifier, sopclassUID)
  READ_FROM_DATASET(DcmUniqueIdentifier, imageUID)
  READ_FROM_DATASET(DcmDecimalString, imagerPixelSpacing)
  READ_FROM_DATASET(DcmDecimalString, pixelSpacing)
  READ_FROM_DATASET(DcmIntegerString, pixelAspectRatio)

  if (result == EC_Normal) result = columns.getUint16(cols_uint,0);
  if (result == EC_Normal) result = rows.getUint16(rows_uint,0);
  if (result == EC_Normal) result = sopclassUID.getString(c_sopclassUID);
  if (result == EC_Normal) result = imageUID.getString(c_imageUID);


  if (EC_Normal == result)
  {
    DVPSDisplayedArea *area = displayedAreaSelectionList.createDisplayedArea(
      referencedSeriesList, c_sopclassUID, c_imageUID, 1, 1, DVPSB_currentImage);
    if (area)
    {
      if (EC_Normal == result) result = area->setDisplayedArea(DVPSD_scaleToFit, (Sint32)1, (Sint32)1, (Sint32)cols_uint, (Sint32)rows_uint);
      if (EC_Normal == result)
      {
        OFBool foundRatio = OFFalse;
        if ((imagerPixelSpacing.getVM()==2)&&(EC_Normal==imagerPixelSpacing.getString(pixelspacing)))
        {
          result = area->setDisplayedAreaPixelSpacing(pixelspacing);
          if (EC_Normal==result) foundRatio = OFTrue;
        }
        if ((! foundRatio)&&(pixelSpacing.getVM()==2)&&(EC_Normal==pixelSpacing.getString(pixelspacing)))
        {
          result = area->setDisplayedAreaPixelSpacing(pixelspacing);
          if (EC_Normal==result) foundRatio = OFTrue;
        }
        if ((! foundRatio)&&(pixelAspectRatio.getVM()==2)&&(EC_Normal==pixelAspectRatio.getString(pixelspacing)))
        {
          result = area->setDisplayedAreaPixelAspectRatio(pixelspacing);
          if (EC_Normal==result) foundRatio = OFTrue;
        }
        if (! foundRatio) result = area->setDisplayedAreaPixelAspectRatio(1.0);
      }
    } else result = EC_MemoryExhausted;
  }
  return result;
}
