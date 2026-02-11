atScanUser (userName, resultUser)
     char    *userName;
     Af_user *resultUser;
{
  char fullName[USER_MAX+HOST_MAX+DOMAIN_MAX+2];
  char *hostPtr, *domainPtr;

  resultUser->af_username[0] = resultUser->af_username[USER_MAX-1] = '\0';
  resultUser->af_userhost[0] = resultUser->af_userhost[HOST_MAX-1] = '\0';
  resultUser->af_userdomain[0] = resultUser->af_userdomain[DOMAIN_MAX-1] = '\0';

  if (!(userName && userName[0]))
    return;

  strcpy (fullName, userName);


  if ((hostPtr = strrchr (fullName, '@')) == NULL) {
    strncpy (resultUser->af_username, fullName, USER_MAX);
    strcpy (resultUser->af_userdomain, af_getdomain());
    return;
  }

  *(hostPtr++) = '\0';
  strncpy (resultUser->af_username, fullName, USER_MAX);


  if (!strcmp (hostPtr, af_getdomain())) {
    strncpy (resultUser->af_userdomain, hostPtr, DOMAIN_MAX);
    return;
  }


  if ((domainPtr = strchr (hostPtr, '.')) == NULL) {
    strncpy (resultUser->af_userhost, hostPtr, HOST_MAX);
    strcpy (resultUser->af_userdomain, af_getdomain());
    return;
  }


  if (!strcmp (domainPtr+1, af_getdomain())) {
    *(domainPtr++) = '\0';
    strncpy (resultUser->af_userhost, hostPtr, HOST_MAX);
    strncpy (resultUser->af_userdomain, domainPtr, DOMAIN_MAX);
    return;
  }


  (void) strncpy (resultUser->af_userdomain, hostPtr, DOMAIN_MAX);
}
