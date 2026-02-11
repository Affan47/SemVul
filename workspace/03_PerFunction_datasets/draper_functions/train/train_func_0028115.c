batchedUnitVectorGetSupportingVertexWithoutMargin(const btVector3* vectors,btVector3* supportVerticesOut,int numVectors) const
{
	for (int i=0;i<numVectors;i++)
	{
		supportVerticesOut[i] = CylinderLocalSupportY(getHalfExtentsWithoutMargin(),vectors[i]);
	}
}
