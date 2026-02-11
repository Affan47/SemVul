Read_mb_u_int32(P_WBXML_INFO buffer, P_WBXML_MB_U_INT32 result)
{
  if (buffer && result)
  {
    int i;
    for (i = 0; i < MAX_MB_U_INT32_BYTES; i++)
    {
      if (BytesLeft(buffer) >= 1)
      {
        (*result)[i] = *(buffer->m_curpos);
        (buffer->m_curpos)++;

        if ( !( (*result)[i] & 0x80 ) )
          break;
      }
      else
      {
        ParseError(ERR_END_OF_DATA);
      }
    }
  }
  else
  {
    ParseError(ERR_INTERNAL_BAD_PARAM);
  }
}
