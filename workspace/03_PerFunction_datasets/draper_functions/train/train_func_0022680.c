M_WriteElements(METAIO_STREAM::ofstream * _fstream, const void * _data,
               METAIO_STL::streamoff _dataQuantity)
  {
  bool localData = false;
  METAIO_STREAM::ofstream* tmpWriteStream;
  if(!strcmp(m_ElementDataFileName, "LOCAL"))
    {
    localData = true;
    tmpWriteStream = _fstream;
    }
  else
    {
    localData = false;
    tmpWriteStream = new METAIO_STREAM::ofstream;

    char dataFileName[255];
    char pathName[255];
    bool usePath = MET_GetFilePath(m_FileName, pathName);
    if(usePath)
      {
      sprintf(dataFileName, "%s%s", pathName, m_ElementDataFileName);
      }
    else
      {
      strcpy(dataFileName, m_ElementDataFileName);
      }


#ifdef __sgi
    {
    METAIO_STREAM::ofstream tFile(dataFileName, METAIO_STREAM::ios::out);
    tFile.close();
    }
    tmpWriteStream->open(dataFileName, METAIO_STREAM::ios::out);
#else
    tmpWriteStream->open(dataFileName, METAIO_STREAM::ios::binary |
                                       METAIO_STREAM::ios::out);
#endif
    }

  if(!m_BinaryData)
    {
    double tf;
    for(int i=0; i<m_Length*m_ElementNumberOfChannels; i++)
      {
      MET_ValueToDouble(m_ElementType, _data, i, &tf);
      if((i+1)/10 == (double)(i+1.0)/10.0)
        {
        (*tmpWriteStream) << tf << METAIO_STREAM::endl;
        }
      else
        {
        (*tmpWriteStream) << tf << " ";
        }
      }
    }
   else
    {
    tmpWriteStream->write( (const char *)_data, (size_t)_dataQuantity );
    }

  if(!localData)
    {
    tmpWriteStream->close();
    delete tmpWriteStream;
    }

  return true;
  }
