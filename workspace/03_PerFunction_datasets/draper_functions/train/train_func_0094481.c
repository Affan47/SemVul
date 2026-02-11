moveInside(Point* p, int distance)
{
    Point ret = *p;
    int64_t bestDist = 2000LL * 2000LL;
    for(unsigned int n=0; n<boundery.size(); n++)
    {
        if (boundery[n].size() < 1)
            continue;
        Point p0 = boundery[n][boundery[n].size()-1];
        for(unsigned int i=0; i<boundery[n].size(); i++)
        {
            Point p1 = boundery[n][i];


            Point pDiff = p1 - p0;
            int64_t lineLength = vSize(pDiff);
            int64_t distOnLine = dot(pDiff, *p - p0) / lineLength;
            if (distOnLine < 10)
                distOnLine = 10;
            if (distOnLine > lineLength - 10)
                distOnLine = lineLength - 10;
            Point q = p0 + pDiff * distOnLine / lineLength;

            int64_t dist = vSize2(q - *p);
            if (dist < bestDist)
            {
                bestDist = dist;
                ret = q + crossZ(normal(p1 - p0, distance));
            }

            p0 = p1;
        }
    }
    if (bestDist < 2000LL * 2000LL)
    {
        *p = ret;
        return true;
    }
    return false;
}
