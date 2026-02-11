RemoveAnalog(AnalogIterator loc)
  {
    if (loc == this->EndAnalog())
    {
      btkWarningMacro("Out of range.");
      return loc;
    }
    Analog::Pointer anl = *loc;
    AnalogIterator it = this->m_Analogs->RemoveItem(loc);
    if ((it == this->EndAnalog()) || (*it !=anl))
      this->Modified();
    return it;
  }
