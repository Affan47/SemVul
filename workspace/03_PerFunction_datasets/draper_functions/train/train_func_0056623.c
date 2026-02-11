mailimap_acl_deleteacl_send(mailstream * fd,
        const char * mailbox,
        const char * identifier)
{
  int r;

  r = mailimap_token_send(fd, "DELETEACL");
  if (r != MAILIMAP_NO_ERROR)
	  return r;

  r = mailimap_space_send(fd);
  if (r != MAILIMAP_NO_ERROR)
    return r;

  r = mailimap_mailbox_send(fd, mailbox);
  if (r != MAILIMAP_NO_ERROR)
    return r;

  r = mailimap_space_send(fd);
  if (r != MAILIMAP_NO_ERROR)
    return r;

  r = mailimap_acl_identifier_send(fd, identifier);
  if (r != MAILIMAP_NO_ERROR)
    return r;

  return MAILIMAP_NO_ERROR;
}
