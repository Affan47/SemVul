acl_free (acl_t * acl)
{
  acl_t *next;

  while (acl)
    {
      next = acl->next;
      regfree (&acl->re);
      netdef_free (acl->netlist);
      free (acl);
      acl = next;
    }
}
