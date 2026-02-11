SetSubKey(const char* sk)
{
  if ( !sk )
    {
    m_SubKey = "";
    m_SubKeySpecified = false;
    }
  else
    {
    m_SubKey = sk;
    m_SubKeySpecified = true;
    }
}
