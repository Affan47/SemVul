ElementNumberOfChannels(int _elementNumberOfChannels)
  {
  if(m_ElementNumberOfChannels != _elementNumberOfChannels)
    {
    InitializeEssential(m_Length, m_ElementType, _elementNumberOfChannels);
    }
  }
