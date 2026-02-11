operator= (const Cgicc& cgi)
{
  this->fEnvironment = cgi.fEnvironment;

  fFormData.clear();
  fFormFiles.clear();

  parseFormInput(fEnvironment.getPostData(), fEnvironment.getContentType());
  parseFormInput(fEnvironment.getQueryString());

  return *this;
}
