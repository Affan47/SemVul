CheckSettings(void)
{

    if (!fAnalyseCube && !fAnalyseDice && !fAnalyseMove) {
        outputl(_("No analysis selected, you must specify at least one type of analysis to perform"));
        return -1;
    }

    return 0;
}
