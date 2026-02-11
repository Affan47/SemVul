toString    (pANTLR3_TOKEN_STREAM ts)
{
    pANTLR3_COMMON_TOKEN_STREAM cts;

    cts	    = (pANTLR3_COMMON_TOKEN_STREAM)ts->super;

    if	(cts->p == -1)
    {
	fillBuffer(cts);
    }

    return  ts->toStringSS(ts, 0, ts->istream->size(ts->istream));
}
