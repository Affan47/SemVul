computeFlexiblySafeTreeLength( double r ) const
{

    double totalLength = 0;
    const RoutingDAG &dag = *(ui.getRoutingDAG() );
    for(unsigned int i = 0; i< dag.getNumEdges(); i++)
    {
        Edge *thisEdge = dag.getEdgePointer(i);

        if(!thisEdge->isTreeEdge() )
        {
            continue;
        }
        double thisLength = computeEdgeLength(thisEdge);
        bool thisEdgeIsUnsafe = thisEdge->isDangerousWeatherWithinLaneWidthW(r,
                                                                             ui.getWeatherDataSets(),
                                                                             ui.getDeviationThreshold(),
                                                                             ui.getNodeEdgeThreshold() );
        if( thisEdgeIsUnsafe == false )
        {
            totalLength += thisLength;
        }
    }

    return totalLength;
}
