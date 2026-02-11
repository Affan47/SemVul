action_handle_echo(event_t *ev, action_t *action)
{
    USE_VAR(ev);
    REQUIRE_RVAL(action->param.string != NULL, 0);
#ifdef ESCREEN
    if (TermWin.screen && TermWin.screen->backend) {
#  ifdef NS_HAVE_SCREEN

        ns_parse_screen_interactive(TermWin.screen, action->param.string);
#  endif
    } else
#endif
        tt_write((unsigned char *) action->param.string, strlen(action->param.string));
    return 1;
}
