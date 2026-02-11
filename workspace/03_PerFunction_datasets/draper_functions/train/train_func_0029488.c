imapdriver_initialize(mailsession * session)
{
  struct imap_session_state_data * data;
  mailimap * imap;
  struct mail_flags_store * flags_store;

  imap = mailimap_new(0, NULL);
  if (imap == NULL)
    goto err;

  flags_store = mail_flags_store_new();
  if (flags_store == NULL)
    goto free_session;

  data = malloc(sizeof(* data));
  if (data == NULL)
    goto free_flags_store;

  data->imap_mailbox = NULL;
  data->imap_session = imap;
  data->imap_flags_store = flags_store;

  session->sess_data = data;

  return MAIL_NO_ERROR;

 free_flags_store:
  mail_flags_store_free(flags_store);
 free_session:
  mailimap_free(imap);
 err:
  return MAIL_ERROR_MEMORY;
}
