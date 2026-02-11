batchedUnitVectorGetSupportingVertexWithoutMargin(const btVector3* vectors,btVector3* supportVerticesOut,int numVectors) const
{

	for (int j=0;j<numVectors;j++)
	{
		btScalar maxDot(btScalar(-BT_LARGE_FLOAT));

		const btVector3& vec = vectors[j];

		btVector3 vtx;
		btScalar newDot;

		const btVector3* pos = &m_localPositionArray[0];
		const btScalar* rad = &m_radiArray[0];
		int numSpheres = m_localPositionArray.size();
		for (int i=0;i<numSpheres;i++)
		{
			vtx = (*pos) +vec*m_localScaling*(*rad) - vec * getMargin();
			pos++;
			rad++;
			newDot = vec.dot(vtx);
			if (newDot > maxDot)
			{
				maxDot = newDot;
				supportVerticesOut[j] = vtx;
			}
		}
	}
}
