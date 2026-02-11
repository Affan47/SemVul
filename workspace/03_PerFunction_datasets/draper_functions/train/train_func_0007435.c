reportSearchPosition(int start, int end, GB_CSTR comment, int mismatches[MAX_MISMATCHES])
{
    ED4_SearchPosition *pos = new ED4_SearchPosition(start, end, reportType, comment, mismatches);
    reportToResult->addSearchPosition(pos);
}
