knocker_conf_parse (void)
{
  FILE *fp;

  char *conf_file = NULL;
  char *linebuff = NULL;
  char *opt_value = NULL;

  conf_file = malloc (strlen (knocker_user.dir) + strlen ("/") + strlen (KNOCKER_CONFIG_FILE) + 1);

  strcpy (conf_file, knocker_user.dir);
  strcat (conf_file, "/");
  strcat (conf_file, KNOCKER_CONFIG_FILE);

  if ((fp = fopen (conf_file, "r")) == NULL)
    {

      free (conf_file);
      knocker_conf_set_default ();
      return -1;
    }

  linebuff = malloc (KNOCKER_CONF_MAX_LEN);
  opt_value = malloc (KNOCKER_CONF_MAX_LEN);

  while (!feof (fp))
    {
      if (_fgetline (fp, linebuff, KNOCKER_CONF_MAX_LEN) == EOF)
        {
          break;
        }

      if (!_iscommented (linebuff, KNOCKER_COMMENT_CHAR))
        {
          if (_isvalid (linebuff, KNOCKER_OPTION_TOKEN))
            {
              if (_getoptval (linebuff, KNOCKER_CONF_OPT_USE_COLORS, opt_value))
                {
                  if (_isno (opt_value))
                       knocker_args.colors = 0;
                  else if  (_isyes (opt_value))
                       knocker_args.colors = 1;
                  else
                       knocker_args.colors = 1;
                }
              else if (_getoptval (linebuff, KNOCKER_CONF_OPT_COLOR_1, opt_value))
                {
                  _set_color_conf (opt_value, 1, 0);
                }
              else if (_getoptval (linebuff, KNOCKER_CONF_OPT_COLOR_2, opt_value))
                {
                  _set_color_conf (opt_value, 2, 0);
                }
              else if (_getoptval (linebuff, KNOCKER_CONF_OPT_COLOR_1_ATTR, opt_value))
                {
                  _set_color_conf (opt_value, 1, 1);
                }
              else if (_getoptval (linebuff, KNOCKER_CONF_OPT_COLOR_2_ATTR, opt_value))
                {
                  _set_color_conf (opt_value, 2, 1);
                }
            }
        }
    }


  fclose (fp);
  free (conf_file);
  free (linebuff);
  free (opt_value);

  return 0;
}
