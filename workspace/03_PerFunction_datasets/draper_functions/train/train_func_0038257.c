SetAnalogNumber(int num)
  {
    if (num == this->GetAnalogNumber())
      return;
    if (this->GetAnalogFrameNumber() == 0)
    {
      btkErrorMacro("The acquisition's duration or the point's frequency is not set.");
      return;
    }
    if (num < this->GetAnalogNumber())
      this->m_Analogs->SetItemNumber(num);
    else
    {
      for (int inc = this->GetAnalogNumber() ; inc < num ; ++inc)
        this->m_Analogs->InsertItem(Analog::New(this->GetAnalogFrameNumber()));
    }
    this->Modified();
  }
