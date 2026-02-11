insertTrace(Trace & newTrace, int netIndex, Score & currentScore, int viaCount, bool incRouted) {
    if (newTrace.gridPoints.count() == 0) {
        DebugDialog::debug("trace with no points");
        return;
    }


    newTrace.netIndex = netIndex;
    newTrace.order = currentScore.traces.values(netIndex).count();
    currentScore.traces.insert(netIndex, newTrace);
    if (incRouted) {
        currentScore.routedCount.insert(netIndex, currentScore.routedCount.value(netIndex) + 1);
        currentScore.totalRoutedCount++;
    }
    currentScore.viaCount.insert(netIndex, currentScore.viaCount.value(netIndex, 0) + viaCount);
    currentScore.totalViaCount += viaCount;
    displayTrace(newTrace);


}
