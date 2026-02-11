removeChildShape(btCollisionShape* shape)
{
	m_updateRevision++;


	for(int i = m_children.size()-1; i >= 0 ; i--)
	{
		if(m_children[i].m_childShape == shape)
		{
			removeChildShapeByIndex(i);
		}
	}


	recalculateLocalAabb();
}
