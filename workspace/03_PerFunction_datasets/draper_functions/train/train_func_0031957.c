GetKey(int idx) const
  {
    if(idx >= _data->Size || idx < 0 ||
        _data->Roster[idx].GetVerificationKey().isNull())
    {
      return EmptyKey();
    }
    return _data->Roster[idx].GetVerificationKey();
  }
