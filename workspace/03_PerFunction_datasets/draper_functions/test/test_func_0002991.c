GetCurrentValue()
    {
    std::string val;
    if(this->CurrentValue.size())
      {
      val.assign(&this->CurrentValue[0], this->CurrentValue.size());
      }
    return val;
    }
