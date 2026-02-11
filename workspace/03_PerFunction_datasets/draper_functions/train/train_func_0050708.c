_cmd_username (char **argv)
{
  assert (argv);

  if (!argv[1]
      || (argv[1] && strlen (argv[1]) <= IPMI_MAX_USER_NAME_LENGTH))
    {
      free (cmd_args.common.username);
      cmd_args.common.username = NULL;

      if (argv[1])
        {
          if (!(cmd_args.common.username = strdup (argv[1])))
            {
              IPMIPOWER_ERROR (("strdup: %s", strerror(errno)));
              exit (1);
            }
        }

      ipmipower_cbuf_printf (ttyout,
                             "username: %s\n",
                             (cmd_args.common.username) ? cmd_args.common.username : "NULL");
    }
  else
    ipmipower_cbuf_printf (ttyout, "username invalid length\n");
}
