s_ndo()
{
    if (!qts_ndo.hasLocalData())
        qts_ndo.setLocalData(new NdoPrivate);
    return qts_ndo.localData();
}
