resetResponseParsing()
{
  m_isRedirection = false;
  m_isChunked = false;
  m_iSize = NO_SIZE;
  clearUnreadBuffer();

  m_responseHeaders.clear();
  m_contentEncodings.clear();
  m_transferEncodings.clear();
  m_contentMD5.clear();
  m_mimeType.clear();

  setMetaData(QLatin1String("request-id"), m_request.id);
}
