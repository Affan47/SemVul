getSOFImageParameters( const JPEGFileMapEntry& entry,
                                                  Uint16& imageWidth,
                                                  Uint16& imageHeight,
                                                  Uint16& samplesPerPixel,
                                                  Uint16& bitsPerSample)
{
  DCMDATA_LIBI2D_DEBUG("I2DJpegSource: Checking for JPEG SOF image parameters");
  if ( (entry.marker < E_JPGMARKER_SOF0) || (entry.marker > E_JPGMARKER_SOF15) )
    return EC_IllegalCall;
  Uint16 length;
  Uint16 image_height, image_width;
  Uint8 data_precision, num_components;
  int result;


  jpegFile.fseek(entry.bytePos, SEEK_SET);
  result = read2Bytes(length);
  if (result == EOF)
    return makeOFCondition(OFM_dcmdata, 18, OF_error, "Premature EOF in JPEG file");


  result = read1Byte(data_precision);
  if (result == EOF)
    return makeOFCondition(OFM_dcmdata, 18, OF_error, "Premature EOF in JPEG file");

  result = read2Bytes(image_height);
  if (result == EOF)
    return makeOFCondition(OFM_dcmdata, 18, OF_error, "Premature EOF in JPEG file");

  result = read2Bytes(image_width);
  if (result == EOF)
    return makeOFCondition(OFM_dcmdata, 18, OF_error, "Premature EOF in JPEG file");

  result = read1Byte(num_components);
  if (result == EOF)
    return makeOFCondition(OFM_dcmdata, 18, OF_error, "Premature EOF in JPEG file");

  imageWidth = image_width;
  imageHeight = image_height;
  samplesPerPixel = num_components;
  bitsPerSample = data_precision;

  DCMDATA_LIBI2D_DEBUG("I2DJpegSource: JPEG SOF image parameters:");
  DCMDATA_LIBI2D_DEBUG("I2DJpegSource:   Image Width: " << image_width);
  DCMDATA_LIBI2D_DEBUG("I2DJpegSource:   Image Height: " << image_height);
  DCMDATA_LIBI2D_DEBUG("I2DJpegSource:   Number of Components: " << num_components);
  DCMDATA_LIBI2D_DEBUG("I2DJpegSource:   Data Precision: " << data_precision);

  if (length != OFstatic_cast(unsigned int, 8 + num_components * 3))
    return makeOFCondition(OFM_dcmdata, 18, OF_error, "Bogus SOF marker length");

  return EC_Normal;
}
