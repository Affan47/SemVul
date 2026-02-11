listSeqregionCompareNameDescending(
    const void *item1,
    const void *item2)
{
    EnsPSeqregion sr1 = *(EnsOSeqregion *const *) item1;
    EnsPSeqregion sr2 = *(EnsOSeqregion *const *) item2;

#if defined(AJ_DEBUG) && AJ_DEBUG >= 2
    if (ajDebugTest("listSeqregionCompareNameDescending"))
        ajDebug("listSeqregionCompareNameDescending\n"
                "  sr1 %p\n"
                "  sr2 %p\n",
                sr1,
                sr2);
#endif


    if (sr1 && (!sr2))
        return -1;

    if ((!sr1) && (!sr2))
        return 0;

    if ((!sr1) && sr2)
        return +1;

    return -1 * ajStrCmpS(sr1->Name, sr2->Name);
}
