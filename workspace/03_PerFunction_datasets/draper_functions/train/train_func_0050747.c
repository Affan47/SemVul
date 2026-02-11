ResizeAnalogNumber(int analogNumber)
  {

    if (analogNumber < this->GetAnalogNumber())
      this->m_Analogs->SetItemNumber(analogNumber);

    for (AnalogIterator it = this->BeginAnalog() ; it != this->EndAnalog() ; ++it)
      (*it)->SetParent(this);

    const int numAnalogs = this->GetAnalogNumber();
    for (int inc = numAnalogs ; inc < analogNumber ; ++inc)
    {
      Analog::Pointer pt = Analog::New(this->m_PointFrameNumber * this->m_AnalogSampleNumberPerPointFrame);
      pt->SetParent(this);
      this->m_Analogs->InsertItem(pt);
    }

    this->Modified();
  }
