_do_sasl_interact (LDAP *ld, unsigned flags, void *defaults, void *_interact)
{
  sasl_interact_t *interact = (sasl_interact_t *)_interact;
  void **args = (void **)defaults;
  int rc;

  while (interact->id != SASL_CB_LIST_END)
    {
      rc = _do_sasl_interaction((pam_handle_t *)args[0], (pam_ldap_session_t *)args[1], flags, interact);
      if (rc != LDAP_SUCCESS)
	return rc;

      interact++;
    }

  return LDAP_SUCCESS;
}
