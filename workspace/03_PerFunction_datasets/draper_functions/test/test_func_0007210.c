__url_set_scheme(URL this, char *url)
{
  if(!strncasecmp(this->url, "http:", 5)){
    this->scheme = HTTP;
    return url+7;
  }
  if(!strncasecmp(this->url, "https:", 6)){
    this->scheme = HTTPS;
    return url+8;
  }
  if(!strncasecmp(this->url, "ftp:", 4)){
    this->scheme = FTP;
    return url+6;
  }
  this->scheme = UNSUPPORTED;
  return url;
}
