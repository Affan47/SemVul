zappable(struct obj *wand)
{
    if(wand->spe < 0 || (wand->spe == 0 && rn2(121)))
            return 0;
    if(wand->spe == 0)
            You("wrest one last charge from the worn-out wand.");
    wand->spe--;
    return 1;
}
