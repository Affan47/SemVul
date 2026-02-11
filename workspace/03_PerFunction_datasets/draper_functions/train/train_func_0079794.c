createProxy(	const btVector3& aabbMin,
															  const btVector3& aabbMax,
															  int ,
															  void* userPtr,
															  short int collisionFilterGroup,
															  short int collisionFilterMask,
															  btDispatcher* ,
															  void* )
{
	btDbvtProxy*		proxy=new(btAlignedAlloc(sizeof(btDbvtProxy),16)) btDbvtProxy(	aabbMin,aabbMax,userPtr,
		collisionFilterGroup,
		collisionFilterMask);

	btDbvtAabbMm aabb = btDbvtVolume::FromMM(aabbMin,aabbMax);


	proxy->stage		=	m_stageCurrent;
	proxy->m_uniqueId	=	++m_gid;
	proxy->leaf			=	m_sets[0].insert(aabb,proxy);
	listappend(proxy,m_stageRoots[m_stageCurrent]);
	if(!m_deferedcollide)
	{
		btDbvtTreeCollider	collider(this);
		collider.proxy=proxy;
		m_sets[0].collideTV(m_sets[0].m_root,aabb,collider);
		m_sets[1].collideTV(m_sets[1].m_root,aabb,collider);
	}
	return(proxy);
}
