ElementByteOrderSwap(void)
  {
  if(META_DEBUG)
    {
    METAIO_STREAM::cout << "MetaArray: ElementByteOrderSwap"
                        << METAIO_STREAM::endl;
    }

  int eSize;
  MET_SizeOfType(m_ElementType, &eSize);
  switch(eSize)
    {
    default:
    case 0:
    case 1:
      {
      break;
      }
    case 2:
      {
      int i;
      for(i=0; i<m_Length*m_ElementNumberOfChannels; i++)
        {
        ((MET_USHORT_TYPE *)m_ElementData)[i] =
              MET_ByteOrderSwapShort(((MET_USHORT_TYPE *)m_ElementData)[i]);
        }
      break;
      }
    case 4:
      {
      int i;
      for(i=0; i<m_Length*m_ElementNumberOfChannels; i++)
        {
        ((MET_UINT_TYPE *)m_ElementData)[i] =
              MET_ByteOrderSwapLong(((MET_UINT_TYPE *)m_ElementData)[i]);
        }
      break;
      }
    case 8:
      {
      int i;
      char* data = (char*)m_ElementData;
      for(i=0; i<m_Length*m_ElementNumberOfChannels; i++)
        {
        MET_ByteOrderSwap8(data);
        data += 8;
        }
      break;
      }
    }
  m_BinaryDataByteOrderMSB = !m_BinaryDataByteOrderMSB;
  }
