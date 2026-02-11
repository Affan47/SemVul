fillHorizon(CHEdgeList& horizon, CHVertex* target)
{
    CHTriangle tri;
    tri.vertex[2] = target;
    tri.removed = false;
    CHEdgeList::iterator it = horizon.begin();
    CHEdgeList::iterator itEnd = horizon.end();
    for (;it != itEnd; it++) {
        tri.vertex[0] = it->first;
        tri.vertex[1] = it->second;
        tri.computeNormal();
        if (isVisible(&tri, mCentroid)) {
            std::swap(tri.vertex[0], tri.vertex[1]);
            tri.computeNormal();
        }
        mHull.push_back(tri);
    }
}
