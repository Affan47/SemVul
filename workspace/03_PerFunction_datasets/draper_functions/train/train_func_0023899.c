LodePNG_inspect(LodePNG_Decoder* decoder, const unsigned char* in, size_t inlength)
{
  if(inlength == 0 || in == 0) { decoder->error = 48; return; }
  if(inlength < 29) { decoder->error = 27; return; }


  LodePNG_InfoPng_cleanup(&decoder->infoPng);
  LodePNG_InfoPng_init(&decoder->infoPng);
  decoder->error = 0;

  if(in[0] != 137 || in[1] != 80 || in[2] != 78 || in[3] != 71 || in[4] != 13 || in[5] != 10 || in[6] != 26 || in[7] != 10) { decoder->error = 28; return; }
  if(in[12] != 'I' || in[13] != 'H' || in[14] != 'D' || in[15] != 'R') { decoder->error = 29; return; }


  decoder->infoPng.width = LodePNG_read32bitInt(&in[16]);
  decoder->infoPng.height = LodePNG_read32bitInt(&in[20]);
  decoder->infoPng.color.bitDepth = in[24];
  decoder->infoPng.color.colorType = in[25];
  decoder->infoPng.compressionMethod = in[26];
  decoder->infoPng.filterMethod = in[27];
  decoder->infoPng.interlaceMethod = in[28];

  if(!decoder->settings.ignoreCrc)
  {
    unsigned CRC = LodePNG_read32bitInt(&in[29]);
    unsigned checksum = Crc32_crc(&in[12], 17);
    if(CRC != checksum) { decoder->error = 57; return; }
  }

  if(decoder->infoPng.compressionMethod != 0) { decoder->error = 32; return; }
  if(decoder->infoPng.filterMethod != 0)      { decoder->error = 33; return; }
  if(decoder->infoPng.interlaceMethod > 1)    { decoder->error = 34; return; }

  decoder->error = checkColorValidity(decoder->infoPng.color.colorType, decoder->infoPng.color.bitDepth);
}
