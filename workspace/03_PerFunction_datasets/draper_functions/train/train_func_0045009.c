hcolor(const char *colorpref)
{
    return (Hallucination || !colorpref) ?
        hcolors[rn2(SIZE(hcolors))] : colorpref;
}
