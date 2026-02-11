argp_version_parser (int key, char *arg, struct argp_state *state)
{
  switch (key)
    {
    case 'V':
      if (argp_program_version_hook)
        (*argp_program_version_hook) (state->out_stream, state);
      else if (argp_program_version)
        fprintf (state->out_stream, "%s\n", argp_program_version);
      else
        __argp_error (state, "%s",
                      dgettext (state->root_argp->argp_domain,
                                "(PROGRAM ERROR) No version known!?"));
      if (! (state->flags & ARGP_NO_EXIT))
        exit (0);
      break;
    default:
      return EBADKEY;
    }
  return 0;
}
