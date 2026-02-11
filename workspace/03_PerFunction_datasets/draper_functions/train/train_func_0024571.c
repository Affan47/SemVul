BytesLeft(P_WBXML_INFO buffer)
{
  if (buffer)
  {
    WBXML_LENGTH bytesRead = (buffer->m_curpos - buffer->m_start);
    if (bytesRead >= buffer->m_length)
    {
      return 0;
    }
    else
    {
      return (buffer->m_length - bytesRead);
    }
  }
  else
  {
    ParseError(ERR_INTERNAL_BAD_PARAM);
  }

  return 0;
}
