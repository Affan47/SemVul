UT_String_findCh(const UT_String &st, char ch)
{
  for (size_t i = 0 ; i < st.size(); i++)
    if (st[i] == ch)
      return i;
  return (size_t)-1;
}
