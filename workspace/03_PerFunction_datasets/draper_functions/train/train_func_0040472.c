parse_opt (int key, char *arg, struct argp_state *state _GL_UNUSED_PARAMETER)
{
  switch (key)
    {
#ifdef  AUTHENTICATION
    case 'a':
      parse_authmode (arg);
      break;
#endif

    case 'D':
      parse_debug_level (arg);
      break;

    case 'E':
      login_invocation = arg;
      break;

    case 'h':
      hostinfo = 0;
      break;

    case 'l':
      parse_linemode (arg);
      break;

    case 'n':
      keepalive = 0;
      break;

#if defined AUTHENTICATION || defined ENCRYPTION
    case 'S':
      principal = arg;
      break;
#endif

    case 'U':
      reverse_lookup = 1;
      break;

#ifdef	AUTHENTICATION
    case 'X':
      auth_disable_name (arg);
      break;
#endif

    default:
      return ARGP_ERR_UNKNOWN;
    }

  return 0;
}
