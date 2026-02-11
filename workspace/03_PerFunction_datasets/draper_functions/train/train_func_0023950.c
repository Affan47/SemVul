get_encrypted_passwd_by_name(char *username)
{
  struct spwd *spwd;

  if ((spwd = getspnam(username)) == NULL) {
	log_err((LOG_ERROR_LEVEL, "getspnam() failed for '%s'", username));
	return(NULL);
  }

  return(strdup(spwd->sp_pwdp));
}
