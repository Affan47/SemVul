next_ldap_entry (struct parse *cfile)
{
  struct ldap_config_stack *temp_stack;

  if (ldap_stack != NULL && ldap_stack->close_brace)
    {
      x_strncat (cfile->inbuf, "}\n", LDAP_BUFFER_SIZE);
      ldap_stack->close_brace = 0;
    }

  while (ldap_stack != NULL &&
         (ldap_stack->ldent == NULL ||
          (ldap_stack->ldent = ldap_next_entry (ld, ldap_stack->ldent)) == NULL))
    {
      if (ldap_stack->close_brace)
        {
          x_strncat (cfile->inbuf, "}\n", LDAP_BUFFER_SIZE);
          ldap_stack->close_brace = 0;
        }

      temp_stack = ldap_stack;
      ldap_stack = ldap_stack->next;
      free_stack_entry (temp_stack);
    }

  if (ldap_stack != NULL && ldap_stack->close_brace)
    {
      x_strncat (cfile->inbuf, "}\n", LDAP_BUFFER_SIZE);
      ldap_stack->close_brace = 0;
    }
}
