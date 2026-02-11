GetNthInput(int idx) const
  {
    if (idx >= static_cast<int>(m_Inputs.size()))
      return DataObject::ConstPointer();
    return m_Inputs[idx];
  }
