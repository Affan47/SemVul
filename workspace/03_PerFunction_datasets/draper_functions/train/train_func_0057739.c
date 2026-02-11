adjustClustersWithAdd(const PolygonInterface& poly,
        const int p_cluster)
{
    for (VertInf *k = vertices.connsBegin(); k != vertices.shapesBegin();
            k = k->lstNext)
    {
        if (inPolyGen(poly, k->point))
        {
            enclosingClusters[k->id].insert(p_cluster);
        }
    }
}
