init(const dtNavMesh* nav, const int maxNodes)
{
	m_nav = nav;

	if (!m_nodePool || m_nodePool->getMaxNodes() < maxNodes)
	{
		if (m_nodePool)
		{
			m_nodePool->~dtNodePool();
			dtFree(m_nodePool);
			m_nodePool = 0;
		}
		m_nodePool = new (dtAlloc(sizeof(dtNodePool), DT_ALLOC_PERM)) dtNodePool(maxNodes, dtNextPow2(maxNodes/4));
		if (!m_nodePool)
			return DT_FAILURE_OUT_OF_MEMORY;
	}
	else
	{
		m_nodePool->clear();
	}

	if (!m_tinyNodePool)
	{
		m_tinyNodePool = new (dtAlloc(sizeof(dtNodePool), DT_ALLOC_PERM)) dtNodePool(64, 32);
		if (!m_tinyNodePool)
			return DT_FAILURE_OUT_OF_MEMORY;
	}
	else
	{
		m_tinyNodePool->clear();
	}


	if (!m_openList || m_openList->getCapacity() < maxNodes)
	{
		if (m_openList)
		{
			m_openList->~dtNodeQueue();
			dtFree(m_openList);
			m_openList = 0;
		}
		m_openList = new (dtAlloc(sizeof(dtNodeQueue), DT_ALLOC_PERM)) dtNodeQueue(maxNodes);
		if (!m_openList)
			return DT_FAILURE_OUT_OF_MEMORY;
	}
	else
	{
		m_openList->clear();
	}

	return DT_SUCCESS;
}
