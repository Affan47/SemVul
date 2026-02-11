computeScore(char* seq1, char* seq2, int gapOp, int gapEx)
{
    int result = 0;
    bool gapSeq1Started = true;
    bool gapSeq2Started = true;
    while ((*seq1 != -1) && (*seq2 != -1))
    {
        if (*seq1==-2)
        {
            if (gapSeq1Started)
                result -= gapEx;
            else
            {
                gapSeq1Started = true;
                result -= gapOp;
            }
        }
        else if (*seq2==-2)
        {
            if (gapSeq2Started)
                result -= gapEx;
            else
            {
                gapSeq2Started = true;
                result -= gapOp;
            }
        }
        else
        {
            result += getScore(*seq1, *seq2);
        }
        seq1++;
        seq2++;
    }
    return result;
}
