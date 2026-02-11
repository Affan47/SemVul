ajRangeSeqExtract(const AjPRange thys, AjPSeq seq)
{
    ajuint nr;
    ajuint i;
    ajuint st;
    ajuint en;
    AjBool result = ajFalse;
    AjPStr outstr = NULL;

    nr = thys->n;

    ajDebug("ajRangeSeqExtract Number:%d\n", nr);

    if (nr)
    {
        for(i = 0; i < nr; i++)
        {
            result = ajTrue;

            if(!ajRangeElementGetValues(thys, i, &st, &en))
                continue;

            ajStrAppendSubS(&outstr, ajSeqGetSeqS(seq), st - 1, en - 1);
            ajDebug("Range [%d] %d..%d '%S'\n", i, st, en, outstr);
        }
        ajSeqAssignSeqS(seq, outstr);
        ajStrDel(&outstr);
    }

    return result;
}
