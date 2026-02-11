aabbTest(const btVector3& aabbMin,const btVector3& aabbMax,btBroadphaseAabbCallback& aabbCallback)
{
	BroadphaseAabbTester callback(aabbCallback);

	const ATTRIBUTE_ALIGNED16(btDbvtVolume)	bounds=btDbvtVolume::FromMM(aabbMin,aabbMax);

	m_sets[0].collideTV(m_sets[0].m_root,bounds,callback);
	m_sets[1].collideTV(m_sets[1].m_root,bounds,callback);

}
