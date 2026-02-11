otp_verify(const otp_option_t *opt,
           const otp_request_t *request, otp_reply_t *reply)
{
  otp_fd_t *fdp;
  int rc;
  int tryagain = 2;

retry:
  if (!tryagain--)
    return -1;
  fdp = otp_getfd(opt);
  if (!fdp || fdp->fd == -1)
    return -1;

  if ((rc = otp_write(fdp, (const char *) request, sizeof(*request))) != sizeof(*request)) {
    if (rc == 0)
      goto retry;
    else
      return -1;
  }

  if ((rc = otp_read(fdp, (char *) reply, sizeof(*reply))) != sizeof(*reply)) {
    if (rc == 0)
      goto retry;
    else
      return -1;
  }


  if (reply->version != 1) {
    (void) radlog(L_AUTH, "rlm_otp: otpd reply for [%s] invalid "
                          "(version %d != 1)",
                  request->username, reply->version);
    otp_putfd(fdp, 1);
    return -1;
  }

  if (reply->passcode[OTP_MAX_PASSCODE_LEN] != '\0') {
    (void) radlog(L_AUTH, "rlm_otp: otpd reply for [%s] invalid (passcode)",
                  request->username);
    otp_putfd(fdp, 1);
    return -1;
  }

  otp_putfd(fdp, 0);
  return reply->rc;
}
