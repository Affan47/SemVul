getAllResponseHeaders(int& ec) const
{
  if (m_state < XHRS_Receiving) {
      ec = DOMException::INVALID_STATE_ERR;
      return jsString("");
  }


  if (responseHeaders.isEmpty()) {
    return jsUndefined();
  }

  int endOfLine = responseHeaders.indexOf("\n");

  if (endOfLine == -1) {
    return jsUndefined();
  }

  return jsString(responseHeaders.mid(endOfLine + 1) + '\n');
}
