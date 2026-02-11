addVertex( CHVertex* vertex )
{
    getOutsideData(vertex)->isInsideHull = true;

    mVisibleTriangles.clear();
    mEdges.clear();
    getVisibleTriangles(vertex, mVisibleTriangles);
    if (mVisibleTriangles.empty()) {
        return 0;
    }
    getHorizon(mVisibleTriangles, mEdges);
    fillHorizon(mEdges, vertex);
    return mEdges.size();
}
