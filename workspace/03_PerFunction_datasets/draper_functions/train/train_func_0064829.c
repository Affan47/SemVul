MET_TypeToString(MET_ValueEnumType _vType, char *_s)
  {
  if(_vType>=0 && _vType<=MET_NUM_VALUE_TYPES)
    {
    strcpy(_s, MET_ValueTypeName[_vType]);
    return true;
    }

  return false;
  }
