GetCaptchaChallenge() {
  if (d_->engine_.get() == NULL)
    return CaptchaChallenge();
  return d_->captcha_challenge_;
}
