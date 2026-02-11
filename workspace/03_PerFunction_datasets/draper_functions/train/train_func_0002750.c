parse_url_login(struct SessionHandle *data,
                                struct connectdata *conn,
                                char **user, char **passwd, char **options)
{
  CURLcode result = CURLE_OK;
  char *userp = NULL;
  char *passwdp = NULL;
  char *optionsp = NULL;


  char *ptr = strchr(conn->host.name, '@');
  char *login = conn->host.name;

  DEBUGASSERT(!**user);
  DEBUGASSERT(!**passwd);
  DEBUGASSERT(!**options);

  if(!ptr)
    goto out;


  conn->host.name = ++ptr;


  if(data->set.use_netrc == CURL_NETRC_REQUIRED)
    goto out;


  result = parse_login_details(login, ptr - login - 1,
                               &userp, &passwdp, &optionsp);
  if(result)
    goto out;

  if(userp) {
    char *newname;


    conn->bits.userpwd_in_url = TRUE;
    conn->bits.user_passwd = TRUE;


    newname = curl_easy_unescape(data, userp, 0, NULL);
    if(!newname) {
      result = CURLE_OUT_OF_MEMORY;
      goto out;
    }

    free(*user);
    *user = newname;
  }

  if(passwdp) {

    char *newpasswd = curl_easy_unescape(data, passwdp, 0, NULL);
    if(!newpasswd) {
      result = CURLE_OUT_OF_MEMORY;
      goto out;
    }

    free(*passwd);
    *passwd = newpasswd;
  }

  if(optionsp) {

    char *newoptions = curl_easy_unescape(data, optionsp, 0, NULL);
    if(!newoptions) {
      result = CURLE_OUT_OF_MEMORY;
      goto out;
    }

    free(*options);
    *options = newoptions;
  }


  out:

  Curl_safefree(userp);
  Curl_safefree(passwdp);
  Curl_safefree(optionsp);

  return result;
}
