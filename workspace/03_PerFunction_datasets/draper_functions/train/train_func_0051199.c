subst_variables (const char  *src,
		 LDAP        *connection,
		 LDAPMessage *entry)
{
  const char *iter;
  char       *retval;
  guint       retval_len;
  guint       pos;

  g_return_val_if_fail (src != NULL, NULL);

  retval_len = strlen (src) + 1;
  pos = 0;

  retval = g_malloc0 (retval_len + 3);


  iter = src;
  while (*iter)
    {
      gboolean performed_subst = FALSE;

      if (pos >= retval_len)
        {
          retval_len *= 2;
          retval = g_realloc (retval, retval_len+3);
        }

      if (*iter == '$' && *(iter + 1) == '(')
        {
          const char *varstart = iter + 2;
          const char *varend   = strchr (varstart, ')');

          if (varend != NULL)
            {
              char *varname;
              char *varval;
              guint varval_len;

              performed_subst = TRUE;

              varname = g_strndup (varstart, varend - varstart);

              varval = get_variable (varname, connection, entry);
              g_free (varname);

              varval_len = strlen (varval);

              if ((retval_len - pos) < varval_len)
                {
                  retval_len = pos + varval_len;
                  retval = g_realloc (retval, retval_len+3);
                }

              strcpy (&retval[pos], varval);
              g_free(varval);
              pos += varval_len;

              iter = varend + 1;
            }
        }

      if (!performed_subst)
        {
          retval[pos] = *iter;
          ++pos;
          ++iter;
        }
    }

  retval[pos] = '\0';

  return retval;
}
