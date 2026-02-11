kfreebsd_setenv (char *env, const char *var, const char *value)
{
  while (1)
    {
      if (env[0] == '\0' && env[1] == '\0')
	{
	  env++;
	  break;
	}
      else
        env++;
    }

  grub_sprintf (env, "%s=%s", var, value);
  env[grub_strlen (env) + 1] = '\0';
}
