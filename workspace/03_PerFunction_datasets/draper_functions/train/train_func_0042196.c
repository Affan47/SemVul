ReadGenericImage(void *out,
                                   unsigned int width,
                                   unsigned int height)
{

  if ( m_ComponentType == UCHAR )
    {
    this->ReadGenericImage<unsigned char>(out, width, height);
    }
  else if ( m_ComponentType == CHAR )
    {
    this->ReadGenericImage<char>(out, width, height);
    }
  else if ( m_ComponentType == USHORT )
    {
    this->ReadGenericImage<unsigned short>(out, width, height);
    }
  else if ( m_ComponentType == SHORT )
    {
    this->ReadGenericImage<short>(out, width, height);
    }
  else if ( m_ComponentType == FLOAT )
    {
    this->ReadGenericImage<float>(out, width, height);
    }
}
