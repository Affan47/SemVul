_get_string_value (LDAP * ld, LDAPMessage * e, const char *attr, char **ptr)
{
  char **vals;
  int rc;

  vals = ldap_get_values (ld, e, (char *) attr);
  if (vals == NULL)
    {
      return PAM_AUTHINFO_UNAVAIL;
    }
  *ptr = strdup (vals[0]);
  if (*ptr == NULL)
    {
      rc = PAM_BUF_ERR;
    }
  else
    {
      rc = PAM_SUCCESS;
    }

  ldap_value_free (vals);

  return rc;
}
