new_domain (const char *name, const char *file_name)
{
  struct msg_domain **p_dom = &domain_list;

  while (*p_dom != NULL && strcmp (name, (*p_dom)->domain_name) != 0)
    p_dom = &(*p_dom)->next;

  if (*p_dom == NULL)
    {
      struct msg_domain *domain;

      domain = XMALLOC (struct msg_domain);
      domain->mlp = message_list_alloc (true);
      domain->domain_name = name;
      domain->file_name = file_name;
      domain->next = NULL;
      *p_dom = domain;
    }

  return *p_dom;
}
