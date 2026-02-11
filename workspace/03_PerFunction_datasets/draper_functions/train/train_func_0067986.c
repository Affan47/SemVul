SetChannel(int idx, Analog::Pointer c)
  {
    if (this->m_Channels->SetItem(idx, c))
      this->Modified();
  }
