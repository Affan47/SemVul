ReadFixedTag(P_WBXML_INFO buffer, WBXML_TAG tag)
{
  if (buffer)
  {
    if (BytesLeft(buffer) >= sizeof(WBXML_TAG))
    {
      if ((*((WBXML_TAG*) buffer->m_curpos)) == tag)
      {
        buffer->m_curpos += sizeof(WBXML_TAG);
      }
      else
      {
        ParseError(ERR_TAG_NOT_FOUND);
      }
    }
    else
    {
      ParseError(ERR_END_OF_DATA);
    }
  }
  else
  {
    ParseError(ERR_INTERNAL_BAD_PARAM);
  }
}
