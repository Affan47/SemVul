create_loveban_request(FXString & request){
  FXMutexLock lock(mutex_data);
  FXTRACE((60,"GMAudioScrobbler::create_loveban_request\n"));
  FXASSERT(mode==SERVICE_LASTFM);

  FXString signature=GMStringFormat("api_key"CLIENT_KEY
                           "artist%s"
                           "methodtrack.love"
                           "sk%s"
                           "track%s"
                           CLIENT_SECRET,
                           submitqueue[0].artist.text(),
                           session.text(),
                           submitqueue[0].title.text());

  checksum(signature);

  request=GMStringFormat("method=track.love"
                         "&track=%s"
                         "&artist=%s"
                         "&api_key="CLIENT_KEY
                         "&api_sig=%s"
                         "&sk=%s",
                         gm_url_encode(submitqueue[0].title).text(),
                         gm_url_encode(submitqueue[0].artist).text(),
                         signature.text(),
                         session.text());
  }
