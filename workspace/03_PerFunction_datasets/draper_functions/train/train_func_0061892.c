addChunk_IDAT(ucvector* out, const unsigned char* data, size_t datasize, LodeZlib_DeflateSettings* zlibsettings)
{
  ucvector zlibdata;
  unsigned error = 0;


  ucvector_init(&zlibdata);
  error = LodePNG_compress(&zlibdata.data, &zlibdata.size, data, datasize, zlibsettings);
  if(!error) error = addChunk(out, "IDAT", zlibdata.data, zlibdata.size);
  ucvector_cleanup(&zlibdata);

  return error;
}
