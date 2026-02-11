mailprivacy_encrypt_msg(struct mailprivacy * privacy,
    char * privacy_driver, char * privacy_encryption,
    mailmessage * msg,
    struct mailmime * mime,
    struct mailmime ** result)
{
  struct mailprivacy_protocol * protocol;
  struct mailprivacy_encryption * encryption;
  int r;

  protocol = get_protocol(privacy, privacy_driver);
  if (protocol == NULL)
    return MAIL_ERROR_INVAL;

  encryption = get_encryption(protocol, privacy_encryption);
  if (encryption == NULL)
    return MAIL_ERROR_INVAL;

  if (encryption->encrypt == NULL)
    return MAIL_ERROR_NOT_IMPLEMENTED;

  r = encryption->encrypt(privacy, msg, mime, result);
  if (r != MAIL_NO_ERROR)
    return r;

  return MAIL_NO_ERROR;
}
