getJFIFImageParameters( const JPEGFileMapEntry& entry,
                                                   Uint16& jfifVersion,
                                                   Uint16& pixelAspectH,
                                                   Uint16& pixelAspectV,
                                                   Uint16& unit)
{
  DCMDATA_LIBI2D_DEBUG("I2DJpegSource: Examining JFIF information");
  if (entry.marker != E_JPGMARKER_APP0)
    return EC_IllegalCall;
  Uint16 jv, pah, pav, unt;


  Uint16 length;
  jpegFile.fseek(entry.bytePos, SEEK_SET);
  int result = read2Bytes(length);
  if (result == EOF)
    return makeOFCondition(OFM_dcmdata, 18, OF_error, "Premature EOF in JPEG file");


  Uint16 twoBytes;
  result = read2Bytes(twoBytes);
  if ( (result == EOF) || (twoBytes != 0x4a46) )
    return makeOFCondition(OFM_dcmdata, 18, OF_error, "Invalid JFIF marker or JFIF marker not found");
  result = read2Bytes(twoBytes);
  if ( (result == EOF) || (twoBytes != 0x4946) )
    return makeOFCondition(OFM_dcmdata, 18, OF_error, "Invalid JFIF marker or JFIF marker not found");
  Uint8 oneByte;
  result = read1Byte(oneByte);
  if ( (result == EOF)|| (oneByte != 0x00) )
    return makeOFCondition(OFM_dcmdata, 18, OF_error, "Invalid JFIF marker or JFIF marker not found");


  result = read2Bytes(twoBytes);
  if (result == EOF)
    return makeOFCondition(OFM_dcmdata, 18, OF_error, "Premature EOF in JPEG file");
  jv = twoBytes;


  result = read1Byte(oneByte);
  if ( (result == EOF) || (oneByte > 2) )
    return makeOFCondition(OFM_dcmdata, 18, OF_error, "Premature EOF in JPEG file");
  unt = oneByte;


  result = read2Bytes(twoBytes);
  if (result == EOF)
    return makeOFCondition(OFM_dcmdata, 18, OF_error, "Premature EOF in JPEG file");
  pah = twoBytes;


  result = read2Bytes(twoBytes);
 if (result == EOF)
    return makeOFCondition(OFM_dcmdata, 18, OF_error, "Premature EOF in JPEG file");
  pav = twoBytes;


  jfifVersion = jv;
  pixelAspectH = pah;
  pixelAspectV = pav;
  unit = unt;

  DCMDATA_LIBI2D_DEBUG("I2DJpegSource: Dumping some JFIF image parameters:");
  DCMDATA_LIBI2D_DEBUG("I2DJpegSource:   JFIF version: " << jfifVersion);
  DCMDATA_LIBI2D_DEBUG("I2DJpegSource:   Horizontal Pixel Aspect Ratio " << pixelAspectH);
  DCMDATA_LIBI2D_DEBUG("I2DJpegSource:   Vertical Pixel Aspect Ratio: " << pixelAspectV);
  DCMDATA_LIBI2D_DEBUG("I2DJpegSource:   Units: " << unit);

  return EC_Normal;
}
