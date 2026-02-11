gpg_command_passphrase(struct mailprivacy * privacy,
    struct mailmessage * msg,
    char * command, char * userid,
    char * stdoutfile, char * stderrfile)
{
  char * passphrase;
  int bad_passphrase;
  int res;
  int r;

  bad_passphrase = 0;

  passphrase = NULL;
  if (userid != NULL)
    passphrase = get_passphrase(privacy, userid);

  res = mailprivacy_spawn_and_wait(command, passphrase, stdoutfile, stderrfile,
      &bad_passphrase);
  if (res != NO_ERROR_PASSPHRASE) {
    switch (res) {
    case ERROR_PASSPHRASE_COMMAND:
      return ERROR_PGP_COMMAND;
    case ERROR_PASSPHRASE_FILE:
      return ERROR_PGP_FILE;
    default:
      return ERROR_PGP_COMMAND;
    }
    return res;
  }

  if (bad_passphrase && (userid == NULL)) {
    char encryption_id[4096];

    encryption_id[0] = '\0';
    r = get_userid(stderrfile, encryption_id, sizeof(encryption_id));
    if (r == 0) {
      passphrase = get_passphrase(privacy, encryption_id);
      if (passphrase == NULL) {
        mailprivacy_gnupg_add_encryption_id(privacy, msg, encryption_id);
        return ERROR_PGP_NOPASSPHRASE;
      }
      else {
        return gpg_command_passphrase(privacy, msg, command, encryption_id,
            stdoutfile, stderrfile);
      }
    }
    else {
      return ERROR_PGP_CHECK;
    }
  }

  if (bad_passphrase && (passphrase != NULL)) {
    return ERROR_PGP_CHECK;
  }

  if (bad_passphrase) {
    mailprivacy_gnupg_add_encryption_id(privacy, msg, userid);
    return ERROR_PGP_NOPASSPHRASE;
  }

  return NO_ERROR_PGP;
}
