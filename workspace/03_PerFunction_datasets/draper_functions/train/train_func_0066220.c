GetWorkCount() {
    int iCount = -1;

    CachedResultsStatusUpdate();
    CachedStateUpdate();

    if (!results.results.empty())
        iCount = (int)results.results.size();

    return iCount;
}
