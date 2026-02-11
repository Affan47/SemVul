rinkj_config_get (const char *config, const char *key)
{
  int ix;
  int ix_eol, ix_next;

  if (config == NULL)
    return NULL;

  for (ix = 0; config[ix]; ix = ix_next)
    {
      char *p_nl;
      int key_ix;

      p_nl = strchr (config + ix, '\n');
      if (p_nl == NULL)
        {

          ix_eol = strlen (config + ix);
          ix_next = ix_eol;
        }
      else
        {
          ix_eol = ix + p_nl - config;
          ix_next = ix_eol + 1;
        }

      for (key_ix = 0; ix + key_ix < ix_eol; key_ix++)
        {
          if (key[key_ix] == 0 && config[ix + key_ix] == ':')
            {
              ix += key_ix + 1;
              while (ix < ix_eol && isspace (config[ix]))
                ix++;
              return rinkj_strdup_size (config + ix, ix_eol - ix);
            }
          else if (key[key_ix] != config[ix + key_ix])
            break;
        }
    }
  return NULL;
}
