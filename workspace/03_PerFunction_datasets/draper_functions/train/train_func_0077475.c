readResponse()
{

  if (int(_response.length()) < _contentLength)
  {
    if ( ! nbRead(_response, &_eof))
    {
      XmlRpcUtil::error("Error in XmlRpcClient::readResponse: read error (%s).",XmlRpcSocket::getErrorMsg().c_str());
      return false;
    }


    if (int(_response.length()) < _contentLength)
    {
      if (_eof)
      {
        XmlRpcUtil::error("Error in XmlRpcClient::readResponse: EOF while reading response");
        return false;
      }
      return true;
    }
  }


  XmlRpcUtil::log(3, "XmlRpcClient::readResponse (read %d bytes)", _response.length());
  XmlRpcUtil::log(5, "response:\n%s", _response.c_str());

  _connectionState = IDLE;

  return false;
}
