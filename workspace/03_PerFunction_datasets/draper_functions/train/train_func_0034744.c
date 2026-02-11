FiftyMoveDraw(void)
{
    if(RepStackSize < 100)
    {
        return false;
    }

    unsigned int pawnhash = Pos.PawnHashValue();
    unsigned int npieces = Pos.TotalMaterial();


    unsigned int plycount = 0;
    for(unsigned int i = RepStackSize; i > 0; i--)
    {
        repeatT * rep = &(RepStack[i - 1]);

        if(npieces != rep->npieces)
        {
            break;
        }
        if(pawnhash != rep->pawnhash)
        {
            break;
        }
        plycount++;
    }
    if(plycount >= 100)
    {
        return true;
    }
    return false;
}
