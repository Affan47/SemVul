processAllOverlappingPairs(btOverlapCallback* callback,btDispatcher* dispatcher)
{

	int i;


	for (i=0;i<m_overlappingPairArray.size();)
	{

		btBroadphasePair* pair = &m_overlappingPairArray[i];
		if (callback->processOverlap(*pair))
		{
			removeOverlappingPair(pair->m_pProxy0,pair->m_pProxy1,dispatcher);

			gOverlappingPairs--;
		} else
		{
			i++;
		}
	}
}
