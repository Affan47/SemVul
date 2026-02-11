extPenalty2(int i, int j)
{
    int h;

    if (!userParameters->getEndGapPenalties() && (j == 0 || j == prfLength2))
    {
        return (0);
    }

    h = (*profile1)[i][LENCOL];
    return (h);
}
