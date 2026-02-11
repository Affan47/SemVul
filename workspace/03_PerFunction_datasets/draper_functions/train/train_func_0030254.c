iexpt10(int e)
{
    if (e < IEXPT10_TABLESIZ) {
        return iexpt10_n[e];
    } else {


        return Scm_Mul(iexpt10_n[IEXPT10_TABLESIZ-1],
                       iexpt10(e - IEXPT10_TABLESIZ + 1));
    }
}
