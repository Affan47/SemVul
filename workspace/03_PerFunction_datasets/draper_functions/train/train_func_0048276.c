ReadStream(METAIO_STREAM::ifstream * _stream)
  {
  if(META_DEBUG)
    {
    METAIO_STREAM::cout << "MetaForm: ReadStream" << METAIO_STREAM::endl;
    }

  M_Destroy();

  fflush(NULL);

  Clear();

  M_SetupReadFields();

  if(m_ReadStream)
    {
    delete m_ReadStream;
    }

  m_ReadStream = _stream;

  bool result = M_Read();

  m_ReadStream= NULL;

  return result;
  }
