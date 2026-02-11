donextdur()
{
    ndurp = TRUE;
    if (isdigit(token[fieldx])) {
        ntime = precise(scanint());
        ntime = scale(ntime, (ulong)time_scale, rate);
        if (token[fieldx])
            fferror("Only digits were expected here");
    } else {
        fieldx++;
        ntime = dodur();
    }
}
