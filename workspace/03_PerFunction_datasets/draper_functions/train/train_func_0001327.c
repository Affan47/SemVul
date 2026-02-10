createProxy(  const btVector3& aabbMin,  const btVector3& aabbMax,int shapeType,void* userPtr, short int collisionFilterGroup,short int collisionFilterMask, btDispatcher* dispatcher,void* )
{


	void* mem = btAlignedAlloc(sizeof(btMultiSapProxy),16);
	btMultiSapProxy* proxy = new (mem)btMultiSapProxy(aabbMin,  aabbMax,shapeType,userPtr, collisionFilterGroup,collisionFilterMask);
	m_multiSapProxies.push_back(proxy);


	setAabb(proxy,aabbMin,aabbMax,dispatcher);
	return proxy;
}
