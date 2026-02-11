ProcessStart() {
  if (d_->pre_auth_.get()) {
    d_->pre_auth_->SignalAuthDone.connect(this, &XmppClient::OnAuthDone);
    d_->pre_auth_->StartPreXmppAuth(
        d_->engine_->GetUser(), d_->server_, d_->pass_, d_->auth_cookie_);
    d_->pass_.Clear();
    return STATE_PRE_XMPP_LOGIN;
  }
  else {
    d_->engine_->SetSaslHandler(new PlainSaslHandler(
              d_->engine_->GetUser(), d_->pass_, d_->allow_plain_));
    d_->pass_.Clear();
    return STATE_START_XMPP_LOGIN;
  }
}
