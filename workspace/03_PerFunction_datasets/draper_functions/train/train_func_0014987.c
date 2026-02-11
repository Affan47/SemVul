processAllTriangles(btTriangleCallback* callback,const btVector3& aabbMin,const btVector3& aabbMax) const
{
	int i = m_mesh_parts.size();
	while(i--)
	{
		m_mesh_parts[i]->processAllTriangles(callback,aabbMin,aabbMax);
	}
}
