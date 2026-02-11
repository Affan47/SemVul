BearoffDumpTwoSided(const bearoffcontext * pbc, const TanBoard anBoard, char *sz)
{
    unsigned int nUs = PositionBearoff(anBoard[1], pbc->nPoints, pbc->nChequers);
    unsigned int nThem = PositionBearoff(anBoard[0], pbc->nPoints, pbc->nChequers);
    unsigned int n = Combination(pbc->nPoints + pbc->nChequers, pbc->nPoints);
    unsigned int iPos = nUs * n + nThem;
    float ar[4];
    unsigned int i;
    const char *aszEquity[] = {
        N_("Cubeless equity"),
        N_("Owned cube"),
        N_("Centered cube"),
        N_("Opponent owns cube")
    };

    sprintf(sz + strlen(sz), "%19s %14s\n%s %12u  %12u\n\n", _("Player"), _("Opponent"), _("Position"), nUs, nThem);

    ReadTwoSidedBearoff(pbc, iPos, ar, NULL);

    if (pbc->fCubeful)
        for (i = 0; i < 4; ++i)
            sprintf(sz + strlen(sz), "%-30.30s: %+7.4f\n", gettext(aszEquity[i]), ar[i]);
    else
        sprintf(sz + strlen(sz), "%-30.30s: %+7.4f\n", gettext(aszEquity[0]), 2.0 * ar[0] - 1.0f);

    strcat(sz, "\n");

    return 0;

}
