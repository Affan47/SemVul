create_handshake_request(FXString & request) {
  FXMutexLock lock(mutex_data);
  FXTRACE((60,"GMAudioScrobbler::create_handshake_request\n"));
  if (mode==SERVICE_LASTFM) {
    FXString signature=GMStringFormat("api_key%smethodauth.getSessiontoken%s%s",CLIENT_KEY,token.text(),CLIENT_SECRET);
    checksum(signature);
    request=GMStringFormat("method=auth.getSession&api_key=%s&api_sig=%s&token=%s",CLIENT_KEY,signature.text(),token.text());
    }
  else {
    FXlong timestamp = FXThread::time()/1000000000;
    FXString timestamp_text = GMStringVal(timestamp);
    FXString tk = password + timestamp_text;
    checksum(tk);
    request=GMStringFormat("/?hs=true&p=1.2&c="CLIENT_ID"&v="CLIENT_VERSION"&u=%s&t=%s&a=%s",username.text(),timestamp_text.text(),tk.text());
    }
  flags&=~(FLAG_LOGIN_CHANGED);
  return mode;
  }
