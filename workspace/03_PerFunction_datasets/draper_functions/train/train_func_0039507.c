ProcessMesh (aiMesh* mesh)
{

	for (unsigned int i = 0; i < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++i)	{
		if (!mesh->mTextureCoords[i])
			mesh->mNumUVComponents[i] = 0;

		else {
			if( !mesh->mNumUVComponents[i])
				mesh->mNumUVComponents[i] = 2;

			aiVector3D* p = mesh->mTextureCoords[i], *end = p+mesh->mNumVertices;


			if (2 == mesh->mNumUVComponents[i]) {
				for (; p != end; ++p)
					p->z = 0.f;
			}
			else if (1 == mesh->mNumUVComponents[i]) {
				for (; p != end; ++p)
					p->z = p->y = 0.f;
			}
			else if (3 == mesh->mNumUVComponents[i]) {


				for (; p != end; ++p) {
					if (p->z != 0)
						break;
				}
				if (p == end) {
					DefaultLogger::get()->warn("ScenePreprocessor: UVs are declared to be 3D but they're obviously not. Reverting to 2D.");
					mesh->mNumUVComponents[i] = 2;
				}
			}
		}
	}


	if (!mesh->mPrimitiveTypes)	{
		for (unsigned int a = 0; a < mesh->mNumFaces; ++a)	{
			aiFace& face = mesh->mFaces[a];
			switch (face.mNumIndices)
			{
			case 3u:
				mesh->mPrimitiveTypes |= aiPrimitiveType_TRIANGLE;
				break;

			case 2u:
				mesh->mPrimitiveTypes |= aiPrimitiveType_LINE;
				break;

			case 1u:
				mesh->mPrimitiveTypes |= aiPrimitiveType_POINT;
				break;

			default:
				mesh->mPrimitiveTypes |= aiPrimitiveType_POLYGON;
				break;
			}
		}
	}


	if (mesh->mTangents && mesh->mNormals && !mesh->mBitangents)	{

		mesh->mBitangents = new aiVector3D[mesh->mNumVertices];
		for (unsigned int i = 0; i < mesh->mNumVertices;++i)	{
			mesh->mBitangents[i] = mesh->mNormals[i] ^ mesh->mTangents[i];
		}
	}
}
