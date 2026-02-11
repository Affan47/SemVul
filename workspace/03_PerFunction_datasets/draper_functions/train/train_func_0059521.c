getTriangles ( core::triangle3df* triangles, s32 arraySize,
	s32& outTriangleCount, const core::matrix4* transform) const
{
	s32 count = TrianglePatches.TotalTriangles;

	if (count > arraySize)
		count = arraySize;

	core::matrix4 mat;

	if (transform)
		mat = (*transform);

	s32 tIndex = 0;

	for (s32 i=0; i<TrianglePatches.NumPatches; ++i)
	{
		if (tIndex + TrianglePatches.TrianglePatchArray[i].NumTriangles <= count)
			for (s32 j=0; j<TrianglePatches.TrianglePatchArray[i].NumTriangles; ++j)
			{
				triangles[tIndex] = TrianglePatches.TrianglePatchArray[i].Triangles[j];

				mat.transformVect(triangles[tIndex].pointA);
				mat.transformVect(triangles[tIndex].pointB);
				mat.transformVect(triangles[tIndex].pointC);

				++tIndex;
			}
	}

	outTriangleCount = tIndex;
}
