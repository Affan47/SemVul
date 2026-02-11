discard_acl (acl_t * mark)
{
  if (mark)
    {
      acl_free (mark->next);
      acl_tail = mark;
      acl_tail->next = NULL;
    }
  else
    acl_head = acl_tail = NULL;
}
