imap_address_to_address(struct mailimap_address * imap_addr,
			    struct mailimf_address ** result)
{
  struct mailimf_address * addr;
  struct mailimf_mailbox * mb;
  int r;
  int res;

  r = imap_address_to_mailbox(imap_addr, &mb);
  if (r != MAIL_NO_ERROR) {
    res = r;
    goto err;
  }

  addr = mailimf_address_new(MAILIMF_ADDRESS_MAILBOX, mb, NULL);
  if (addr == NULL) {
    res = MAIL_ERROR_MEMORY;
    goto free_mb;
  }

  * result = addr;

  return MAIL_NO_ERROR;

 free_mb:
  mailimf_mailbox_free(mb);
 err:
  return res;
}
