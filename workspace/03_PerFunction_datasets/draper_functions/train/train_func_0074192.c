convert_ulonglong_to_string(MET_ULONG_LONG_TYPE val)
  {
  std::string result;
  while (val > 0)
    {
    result = static_cast<char>((val % 10)+ '0') + result;
    val /= 10;
    }
  return result;
  }
