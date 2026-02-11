parseResponse(XmlRpcValue& result)
{
  std::string r;
  _response.swap(r);


  bool emptyParam;
  int offset = 0;
  if ( ! XmlRpcUtil::findTag("methodResponse",r,&offset,&emptyParam) || emptyParam)
  {
    XmlRpcUtil::error("Error in XmlRpcClient::parseResponse: Invalid response - no methodResponse. Response:\n%s", r.c_str());
    return false;
  }


  if (XmlRpcUtil::nextTagIs("params",r,&offset,&emptyParam) &&
      XmlRpcUtil::nextTagIs("param",r,&offset,&emptyParam))
  {
    if (emptyParam)
    {
      result = 0;
    }
    else if (  ! result.fromXml(r, &offset))
    {
      XmlRpcUtil::error("Error in XmlRpcClient::parseResponse: Invalid response value. Response:\n%s", r.c_str());
      return false;
    }
  }
  else if (XmlRpcUtil::nextTagIs("fault",r,&offset,&emptyParam))
  {
    _isFault = true;

    if (emptyParam || ! result.fromXml(r, &offset))
    {
      result = 0;
      return false;
    }
  }
  else
  {
    XmlRpcUtil::error("Error in XmlRpcClient::parseResponse: Invalid response - no param or fault tag. Response:\n%s", r.c_str());
    return false;
  }

  return result.valid();
}
