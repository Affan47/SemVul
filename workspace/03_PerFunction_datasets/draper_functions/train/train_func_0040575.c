destroy_mbox_list (struct rfc2822_header *header)
{
  struct mbox *mbox, *next;

  assert (header != NULL);

  mbox = header->value;
  while (mbox != NULL)
    {
      next = mbox->next;
      if (mbox->phrase != NULL)
        free ((void *) mbox->phrase);
      if (mbox->mailbox != NULL)
        free ((void *) mbox->mailbox);
      free (mbox);
      mbox = next;
    }
}
