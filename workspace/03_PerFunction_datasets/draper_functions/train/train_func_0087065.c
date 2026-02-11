ReadKeyValueU16(std::vector<uint16_t>& val, IEEELittleEndianBinaryFileStream* bifs, int key)
  {
    this->ReadKey(bifs, key);
    int16_t size = bifs->ReadU16();
    val.resize(size * 2);
    for (int i = 0 ; i < static_cast<int>(val.size()) ; ++i)
      val[i] = bifs->ReadU16();
    return 1 + size;
  }
