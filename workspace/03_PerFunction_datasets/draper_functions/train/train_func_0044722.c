CompressBuffer(const unsigned char* uncompressedData,
                                      unsigned long uncompressedSize,
                                      unsigned char* compressedData,
                                      unsigned long compressionSpace)
{
  unsigned long compressedSize = compressionSpace;
  Bytef* cd = reinterpret_cast<Bytef*>(compressedData);
  const Bytef* ud = reinterpret_cast<const Bytef*>(uncompressedData);


  if(compress2(cd, &compressedSize, ud, uncompressedSize, this->CompressionLevel) != Z_OK)
    {
    vtkErrorMacro("Zlib error while compressing data.");
    return 0;
    }

  return compressedSize;
}
