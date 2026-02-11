intersectChains()
{
    MCIndexSegmentSetMutualIntersector::SegmentOverlapAction overlapAction( *segInt);

    for (MonoChains::size_type i = 0, ni = monoChains.size(); i < ni; ++i)
    {
        MonotoneChain * queryChain = (MonotoneChain *)monoChains[i];

        std::vector<void*> overlapChains;
        index->query( &(queryChain->getEnvelope()), overlapChains);

        for (std::size_t j = 0, nj = overlapChains.size(); j < nj; j++)
        {
            MonotoneChain * testChain = (MonotoneChain *)(overlapChains[j]);

            queryChain->computeOverlaps( testChain, &overlapAction);
            nOverlaps++;
            if (segInt->isDone())
                return;
        }
    }
}
