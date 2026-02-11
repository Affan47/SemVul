GetMeshVFormatUnique(const aiMesh* pcMesh)
{
	ai_assert(NULL != pcMesh);


	unsigned int iRet = 1;


	if (pcMesh->HasNormals())iRet |= 0x2;

	if (pcMesh->HasTangentsAndBitangents())iRet |= 0x4;

#ifdef BOOST_STATIC_ASSERT
	BOOST_STATIC_ASSERT(8 >= AI_MAX_NUMBER_OF_COLOR_SETS);
	BOOST_STATIC_ASSERT(8 >= AI_MAX_NUMBER_OF_TEXTURECOORDS);
#endif


	unsigned int p = 0;
	while (pcMesh->HasTextureCoords(p))
	{
		iRet |= (0x100 << p);
		if (3 == pcMesh->mNumUVComponents[p])
			iRet |= (0x10000 << p);

		++p;
	}

	p = 0;
	while (pcMesh->HasVertexColors(p))iRet |= (0x1000000 << p++);
	return iRet;
}
