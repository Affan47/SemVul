isTSIOk(const fxStr& tsi)
{
    updatePatterns(qualifyTSI, tsiPats, acceptTSI, lastTSIModTime);
    return (qualifyTSI == "" ? true : checkACL(tsi, tsiPats, *acceptTSI));
}
