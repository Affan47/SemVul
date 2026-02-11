parse_screen_status_if_necessary(void)
{
    ns_parse_screen(TermWin.screen, (TermWin.screen_pending > 1),
                    TERM_WINDOW_GET_REPORTED_COLS(), screen.text[TERM_WINDOW_GET_REPORTED_ROWS() + TermWin.saveLines - 1]);
    if (TermWin.screen_pending > 1)
        TermWin.screen_pending = 0;
}
