bc_push_arg (const struct buildcmd_control *ctl,
             struct buildcmd_state *state,
             const char *arg, size_t len,
             const char *prefix, size_t pfxlen,
             int initial_args)
{
  if (!initial_args)
    {
      state->todo = 1;
    }

  if (arg)
    {


      if (state->cmd_argv_chars + len > ctl->arg_max)
        {
          if (initial_args || state->cmd_argc == ctl->initial_argc)
            error (1, 0, _("can not fit single argument within argument list size limit"));

          if (ctl->replace_pat
              || (ctl->exit_if_size_exceeded &&
                  (ctl->lines_per_exec || ctl->args_per_exec)))
            error (1, 0, _("argument list too long"));
          do_exec (ctl, state);
        }


      if (bc_argc_limit_reached(initial_args, ctl, state))
	do_exec (ctl, state);
    }

  if (state->cmd_argc >= state->cmd_argv_alloc)
    {

      if (!state->cmd_argv)
        {
          state->cmd_argv_alloc = 64;
          state->cmd_argv = xmalloc (sizeof (char *) * state->cmd_argv_alloc);
        }
      else
        {
          state->cmd_argv_alloc *= 2;
          state->cmd_argv = xrealloc (state->cmd_argv,
				      sizeof (char *) * state->cmd_argv_alloc);
        }
    }

  if (!arg)
    state->cmd_argv[state->cmd_argc++] = NULL;
  else
    {
      state->cmd_argv[state->cmd_argc++] = state->argbuf + state->cmd_argv_chars;
      if (prefix)
        {
          strcpy (state->argbuf + state->cmd_argv_chars, prefix);
          state->cmd_argv_chars += pfxlen;
        }

      strcpy (state->argbuf + state->cmd_argv_chars, arg);
      state->cmd_argv_chars += len;


      if (bc_argc_limit_reached(initial_args, ctl, state))
	do_exec (ctl, state);
    }


  if (initial_args)
    {
      state->cmd_initial_argv_chars = state->cmd_argv_chars;
    }
}
