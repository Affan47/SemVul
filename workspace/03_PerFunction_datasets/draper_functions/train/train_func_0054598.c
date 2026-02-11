password_match (const char *password, const char *hash)
{
  if (strlen(password) && strlen(hash))
    {
      if (! strncmp (hash, "$0$", 3))
	{

	  return match (password, hash+3, TRUE);
	}
      else
	{
#ifdef HAVE_LIBCRYPT

	  char *encrypted = crypt (password, hash);
	  return encrypted && ! strcmp (encrypted, hash);
#else

	  return FALSE;
#endif
	}
    }
  else
    {
      if (strlen(password))
	{
	  return FALSE;
	}
      else
	{
	  return ! strlen(hash) ;
	}
    }
}
