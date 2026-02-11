smtp_perform_authentication(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  const char *mech = NULL;
  char *initresp = NULL;
  size_t len = 0;
  smtpstate state1 = SMTP_STOP;
  smtpstate state2 = SMTP_STOP;


  if(!conn->bits.user_passwd) {
    state(conn, SMTP_STOP);

    return result;
  }


  result = smtp_calc_sasl_details(conn, &mech, &initresp, &len, &state1,
                                  &state2);

  if(!result) {
    if(mech) {

      result = smtp_perform_auth(conn, mech, initresp, len, state1, state2);

      Curl_safefree(initresp);
    }
    else {

      infof(conn->data, "No known authentication mechanisms supported!\n");
      result = CURLE_LOGIN_DENIED;
    }
  }

  return result;
}
