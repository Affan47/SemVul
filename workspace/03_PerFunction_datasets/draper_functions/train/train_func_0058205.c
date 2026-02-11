hasCost(EventType* ct)
{
    if (subCost(ct) >0)
        return true;

    foreach(TraceLineCall* lc, _lineCalls)
        if (lc->subCost(ct) >0)
            return true;

    foreach(TraceLineJump* lj, _lineJumps)
        if (lj->executedCount() >0)
            return true;

    return false;
}
