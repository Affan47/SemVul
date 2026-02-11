CommandShowPlayer(char *UNUSED(sz))
{

    int i;

    for (i = 0; i < 2; i++) {
        outputf(_("Player %d:\n" "  Name: %s\n" "  Type: "), i, ap[i].szName);

        switch (ap[i].pt) {
        case PLAYER_EXTERNAL:
            outputf(_("external: %s\n\n"), ap[i].szSocket);
            break;
        case PLAYER_GNU:
            outputf(_("gnubg:\n"));
            outputl(_("    Checker play:"));
            ShowEvalSetup(&ap[i].esChequer);
            outputl(_("    Move filters:"));
            ShowMoveFilters(ap[i].aamf);
            outputl(_("    Cube decisions:"));
            ShowEvalSetup(&ap[i].esCube);
            break;
        case PLAYER_HUMAN:
            outputl(_("human\n"));
            break;
        }
    }
}
