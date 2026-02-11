override_login(struct SessionHandle *data,
                               struct connectdata *conn,
                               char **userp, char **passwdp, char **optionsp)
{
  if(data->set.str[STRING_USERNAME]) {
    free(*userp);
    *userp = strdup(data->set.str[STRING_USERNAME]);
    if(!*userp)
      return CURLE_OUT_OF_MEMORY;
  }

  if(data->set.str[STRING_PASSWORD]) {
    free(*passwdp);
    *passwdp = strdup(data->set.str[STRING_PASSWORD]);
    if(!*passwdp)
      return CURLE_OUT_OF_MEMORY;
  }

  if(data->set.str[STRING_OPTIONS]) {
    free(*optionsp);
    *optionsp = strdup(data->set.str[STRING_OPTIONS]);
    if(!*optionsp)
      return CURLE_OUT_OF_MEMORY;
  }

  conn->bits.netrc = FALSE;
  if(data->set.use_netrc != CURL_NETRC_IGNORED) {
    if(Curl_parsenetrc(conn->host.name,
                       userp, passwdp,
                       data->set.str[STRING_NETRC_FILE])) {
      infof(data, "Couldn't find host %s in the "
            DOT_CHAR "netrc file; using defaults\n",
            conn->host.name);
    }
    else {


      conn->bits.netrc = TRUE;

      conn->bits.user_passwd = TRUE;
    }
  }

  return CURLE_OK;
}
