service(FXuint s) {
  FXTRACE((60,"GMAudioScrobbler::service\n"));
  if (s==SERVICE_LASTFM || s==SERVICE_LIBREFM) {

    mutex_data.lock();

    if (s==SERVICE_LASTFM)
      FXApp::instance()->reg().writeStringEntry("LastFM","handshake-url",LASTFM_URL);
    else
      FXApp::instance()->reg().writeStringEntry("LastFM","handshake-url",LIBREFM_URL);

    handshake_url=FXApp::instance()->reg().readStringEntry("LastFM","handshake-url",LASTFM_URL);
    nowplaying_url.clear();
    submit_url.clear();
    session.clear();
    token.clear();

    flags|=FLAG_SERVICE;
    flags&=~FLAG_BADAUTH|FLAG_TIMEOUT|FLAG_BANNED|FLAG_BADTIME;

    username.clear();
    password.clear();
    FXApp::instance()->reg().writeStringEntry("LastFM","username",username.text());
    FXApp::instance()->reg().writeStringEntry("LastFM","password",password.text());
    FXApp::instance()->reg().writeStringEntry("LastFM","session","");
    FXApp::instance()->reg().writeBoolEntry("LastFM","client-banned",false);

    mode=s;

    reset_timeout();
    mutex_data.unlock();

    wakeup();
    }
  }
