MET_StringToType(const char *_s, MET_ValueEnumType *_vType)
  {
  int i;
  for(i=0; i<MET_NUM_VALUE_TYPES; i++)
    {
    if(!strcmp(_s, MET_ValueTypeName[i]))
      {
      *_vType = (MET_ValueEnumType)i;
      return true;
      }
    }

  *_vType = MET_OTHER;
  return false;
  }
