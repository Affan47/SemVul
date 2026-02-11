create_token_request(FXString & request) {
  FXMutexLock lock(mutex_data);
  FXTRACE((60,"GMAudioScrobbler::create_token_request\n"));
  FXString signature="api_key"CLIENT_KEY"methodauth.getToken"CLIENT_SECRET;
  checksum(signature);
  request=GMStringFormat("method=auth.getToken&api_key="CLIENT_KEY"&api_sig=%s",signature.text());
  flags&=~(FLAG_LOGIN_CHANGED);
  }
