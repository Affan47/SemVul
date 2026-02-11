decodeFrame(
    const DcmRepresentationParameter * ,
    DcmPixelSequence *fromPixSeq,
    const DcmCodecParameter *cp,
    DcmItem *dataset,
    Uint32 frameNo,
    Uint32& currentItem,
    void * buffer,
    Uint32 bufSize,
    OFString& decompressedColorModel) const
{
  OFCondition result = EC_Normal;


  const DJLSCodecParameter *djcp = OFreinterpret_cast(const DJLSCodecParameter *, cp);


  Uint16 imageSamplesPerPixel = 0;
  if (dataset->findAndGetUint16(DCM_SamplesPerPixel, imageSamplesPerPixel).bad()) return EC_TagNotFound;

  if ((imageSamplesPerPixel != 3) && (imageSamplesPerPixel != 1)) return EC_InvalidTag;

  Uint16 imageRows = 0;
  if (dataset->findAndGetUint16(DCM_Rows, imageRows).bad()) return EC_TagNotFound;
  if (imageRows < 1) return EC_InvalidTag;

  Uint16 imageColumns = 0;
  if (dataset->findAndGetUint16(DCM_Columns, imageColumns).bad()) return EC_TagNotFound;
  if (imageColumns < 1) return EC_InvalidTag;

  Uint16 imageBitsStored = 0;
  if (dataset->findAndGetUint16(DCM_BitsStored, imageBitsStored).bad()) return EC_TagNotFound;

  Uint16 imageBitsAllocated = 0;
  if (dataset->findAndGetUint16(DCM_BitsAllocated, imageBitsAllocated).bad()) return EC_TagNotFound;


  if ((imageBitsStored < 1) || (imageBitsStored > 16)) return EC_JLSUnsupportedBitDepth;


  Uint16 bytesPerSample = 1;
  if (imageBitsStored > 8) bytesPerSample = 2;
  else if (imageBitsAllocated > 8) bytesPerSample = 2;


  Sint32 imageFrames = 0;
  dataset->findAndGetSint32(DCM_NumberOfFrames, imageFrames).good();

  if (imageFrames >= OFstatic_cast(Sint32, fromPixSeq->card()))
    imageFrames = fromPixSeq->card() - 1;
  if (imageFrames < 1)
    imageFrames = 1;


  if (currentItem == 0)
  {
    result = determineStartFragment(frameNo, imageFrames, fromPixSeq, currentItem);
  }

  if (result.good())
  {

    DCMJPLS_DEBUG("Starting to decode frame " << frameNo << " with fragment " << currentItem);
    result = decodeFrame(fromPixSeq, djcp, dataset, frameNo, currentItem, buffer, bufSize,
        imageFrames, imageColumns, imageRows, imageSamplesPerPixel, bytesPerSample);
  }

  if (result.good())
  {

    result = dataset->findAndGetOFString(DCM_PhotometricInterpretation, decompressedColorModel);
  }

  return result;
}
