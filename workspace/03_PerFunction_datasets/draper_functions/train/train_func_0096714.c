readEnvironmentVariables(CgiInput *input)
{
  fServerSoftware 	= input->getenv("SERVER_SOFTWARE");
  fServerName 		= input->getenv("SERVER_NAME");
  fGatewayInterface 	= input->getenv("GATEWAY_INTERFACE");
  fServerProtocol 	= input->getenv("SERVER_PROTOCOL");

  std::string port 	= input->getenv("SERVER_PORT");
  fServerPort 		= std::atol(port.c_str());

  fRequestMethod 	= input->getenv("REQUEST_METHOD");
  fPathInfo 		= input->getenv("PATH_INFO");
  fPathTranslated 	= input->getenv("PATH_TRANSLATED");
  fScriptName 		= input->getenv("SCRIPT_NAME");
  fQueryString 		= input->getenv("QUERY_STRING");
  fRemoteHost 		= input->getenv("REMOTE_HOST");
  fRemoteAddr 		= input->getenv("REMOTE_ADDR");
  fAuthType 		= input->getenv("AUTH_TYPE");
  fRemoteUser 		= input->getenv("REMOTE_USER");
  fRemoteIdent 		= input->getenv("REMOTE_IDENT");
  fContentType 		= input->getenv("CONTENT_TYPE");

  std::string length 	= input->getenv("CONTENT_LENGTH");
  fContentLength 	= std::atol(length.c_str());

  fAccept 		= input->getenv("HTTP_ACCEPT");
  fUserAgent 		= input->getenv("HTTP_USER_AGENT");
  fRedirectRequest 	= input->getenv("REDIRECT_REQUEST");
  fRedirectURL 		= input->getenv("REDIRECT_URL");
  fRedirectStatus 	= input->getenv("REDIRECT_STATUS");
  fReferrer 		= input->getenv("HTTP_REFERER");
  fCookie 		= input->getenv("HTTP_COOKIE");


  std::string https 	= input->getenv("HTTPS");
  if(stringsAreEqual(https, "on"))
    fUsingHTTPS = true;
  else
    fUsingHTTPS = false;


}
