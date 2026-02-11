M_ReadElements(METAIO_STREAM::ifstream * _fstream, void * _data,
               METAIO_STL::streamoff _dataQuantity)
  {
  if(META_DEBUG)
    {
    METAIO_STREAM::cout << "MetaImage: M_ReadElements" << METAIO_STREAM::endl;
    }

  if(m_HeaderSize>(int)0)
    {
    _fstream->seekg(m_HeaderSize, METAIO_STREAM::ios::beg);
    if(!_fstream->good())
      {
      METAIO_STREAM::cerr << "MetaImage: Read: header not read correctly"
                          << METAIO_STREAM::endl;
      return false;
      }
    }

  int elementSize;
  MET_SizeOfType(m_ElementType, &elementSize);
  METAIO_STL::streamoff readSize = _dataQuantity*m_ElementNumberOfChannels*elementSize;
  if(META_DEBUG)
    {
    METAIO_STREAM::cout << "MetaImage: M_ReadElements: ReadSize = "
                        << readSize << METAIO_STREAM::endl;
    }

  if(m_HeaderSize == -1)
    {
    if(META_DEBUG)
      {
      METAIO_STREAM::cout << "MetaImage: M_ReadElements: Skipping header"
                          << METAIO_STREAM::endl;
      }
    _fstream->seekg(-readSize, METAIO_STREAM::ios::end);
    }


  if(m_BinaryData && m_CompressedData)
    {


    bool compressedDataDeterminedFromFile = false;
    if(m_CompressedDataSize==0)
      {
      compressedDataDeterminedFromFile = true;
      _fstream->seekg(0, METAIO_STREAM::ios::end);
      m_CompressedDataSize = _fstream->tellg();
      _fstream->seekg(0, METAIO_STREAM::ios::beg);
      }

    unsigned char* compr = new unsigned char[m_CompressedDataSize];

    M_ReadElementData( _fstream, compr, m_CompressedDataSize );

    MET_PerformUncompression(compr, m_CompressedDataSize,
                             (unsigned char *)_data, readSize);

    if (compressedDataDeterminedFromFile)
      {
      m_CompressedDataSize = 0;
      }

    delete [] compr;
    }
  else
    {
    if(!m_BinaryData)
      {

      M_ReadElementData( _fstream, _data, _dataQuantity );

      }
    else
      {

      if ( !M_ReadElementData( _fstream, _data, _dataQuantity ) )
        return false;

      }
    }

  return true;
  }
