CommandShowDisplay(char *UNUSED(sz))
{

    if (fDisplay)
        outputl(_("GNU Backgammon will display boards for computer moves."));
    else
        outputl(_("GNU Backgammon will not display boards for computer moves."));
}
