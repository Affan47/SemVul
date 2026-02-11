ns_screen_weird(_ns_sess * screen, long type, char *doc)
{
    if (!(err_inhibit & type)) {
        err_inhibit |= type;
        ns_desc_sess(screen, "ns_screen_weird");
        fprintf(stderr, "parse_screen: %s (%ld) screen sent weird stuff.\n"
                "This should never happen. It is assumed that you use a\n"
                "rather unusual configuration for \"screen\".   Please\n"
                "send the result of 'screen --version' to <scream@azundris.com>\n"
                "(together with your ~/.screenrc and /etc/screenrc if present).\n"
                "If at all possible, please also run 'Eterm -e screen' and make\n"
                "a screenshot of the offending window (and the window only, the\n"
                "beauty of your desktop is not relevant to this investigation. : ).\n", doc, type);
    }
    (void) ns_upd_stat(screen);
    return NS_FAIL;
}
