convertBytes(const char *const in, const unsigned length, std::vector<char> &out)
{
  assert(m_converterToUnicode);
  assert(m_converterToUTF8);

  UErrorCode status = U_ZERO_ERROR;
  if (out.empty())
    out.resize(length);

  unsigned outLength;

  do
  {
    const char *inText = in;
    char *outText = &out[0];
    status = U_ZERO_ERROR;
    ucnv_convertEx(
      m_converterToUTF8, m_converterToUnicode,
      &outText, outText + out.size(), &inText, inText + length,
      0, 0, 0, 0,
      TRUE, TRUE, &status)
    ;

    switch (status)
    {
    case U_BUFFER_OVERFLOW_ERROR :
      out.resize(out.size() + length);
      break;
    case U_STRING_NOT_TERMINATED_WARNING :
      status = U_ZERO_ERROR;

    case U_ZERO_ERROR :
      outLength = static_cast<unsigned>(outText - &out[0]);
      break;
    default :
      return false;
    }
  }
  while (U_ZERO_ERROR != status);

  out.erase(out.begin() + outLength, out.end());
  out.push_back(0);

  return true;
}

}
