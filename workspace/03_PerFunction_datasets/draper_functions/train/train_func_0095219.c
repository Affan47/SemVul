copy_pwd_changes (struct passwd *dest, struct passwd *src,
		  char *buffer, size_t buflen)
{
  if (src->pw_passwd != NULL && strlen (src->pw_passwd))
    {
      if (buffer == NULL)
	dest->pw_passwd = strdup (src->pw_passwd);
      else if (dest->pw_passwd &&
	       strlen (dest->pw_passwd) >= strlen (src->pw_passwd))
	strcpy (dest->pw_passwd, src->pw_passwd);
      else
	{
	  dest->pw_passwd = buffer;
	  strcpy (dest->pw_passwd, src->pw_passwd);
	  buffer += strlen (dest->pw_passwd) + 1;
	  buflen = buflen - (strlen (dest->pw_passwd) + 1);
	}
    }

  if (src->pw_gecos != NULL && strlen (src->pw_gecos))
    {
      if (buffer == NULL)
	dest->pw_gecos = strdup (src->pw_gecos);
      else if (dest->pw_gecos &&
	       strlen (dest->pw_gecos) >= strlen (src->pw_gecos))
	strcpy (dest->pw_gecos, src->pw_gecos);
      else
	{
	  dest->pw_gecos = buffer;
	  strcpy (dest->pw_gecos, src->pw_gecos);
	  buffer += strlen (dest->pw_gecos) + 1;
	  buflen = buflen - (strlen (dest->pw_gecos) + 1);
	}
    }
  if (src->pw_dir != NULL && strlen (src->pw_dir))
    {
      if (buffer == NULL)
	dest->pw_dir = strdup (src->pw_dir);
      else if (dest->pw_dir && strlen (dest->pw_dir) >= strlen (src->pw_dir))
	strcpy (dest->pw_dir, src->pw_dir);
      else
	{
	  dest->pw_dir = buffer;
	  strcpy (dest->pw_dir, src->pw_dir);
	  buffer += strlen (dest->pw_dir) + 1;
	  buflen = buflen - (strlen (dest->pw_dir) + 1);
	}
    }

  if (src->pw_shell != NULL && strlen (src->pw_shell))
    {
      if (buffer == NULL)
	dest->pw_shell = strdup (src->pw_shell);
      else if (dest->pw_shell &&
	       strlen (dest->pw_shell) >= strlen (src->pw_shell))
	strcpy (dest->pw_shell, src->pw_shell);
      else
	{
	  dest->pw_shell = buffer;
	  strcpy (dest->pw_shell, src->pw_shell);
	  buffer += strlen (dest->pw_shell) + 1;
	  buflen = buflen - (strlen (dest->pw_shell) + 1);
	}
    }
}
