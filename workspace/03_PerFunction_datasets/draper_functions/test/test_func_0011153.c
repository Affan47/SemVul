ReadData(void *data, SizeType bytes) ITK_OVERRIDE
  {
    if ( m_File == ITK_NULLPTR )
      {
      ExceptionObject exception;
      exception.SetDescription("File cannot be read");
      throw exception;
      }

    const SizeValueType numberOfBytesToRead =  Math::CastWithRangeCheck< SizeValueType, SizeType >(bytes);
    SizeType     bread = fread(data, NumericTraits< SizeValueType >::One, numberOfBytesToRead, m_File);
    if ( bread != bytes )
      {
      itksys_ios::ostringstream oss;
      oss << "File size does not match header: "
          << bytes << " bytes requested but only "
          << bread << " bytes available!" << std::endl
          << "At file position " << ftell(m_File);
      ExceptionObject exception;
      exception.SetDescription( oss.str().c_str() );
      throw exception;
      }
  }
