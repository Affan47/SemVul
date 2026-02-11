_cli_out (const char *fmt, ...)
{
        struct cli_state *state = NULL;
        va_list           ap;
        int               ret = 0;

        state = global_state;

        va_start (ap, fmt);

#ifdef HAVE_READLINE
        if (state->rl_enabled && !state->rl_processing)
                return cli_rl_out(state, fmt, ap);
#endif

        ret = vprintf (fmt, ap);
        printf ("\n");
        va_end (ap);

        return ret;
}
