UpdateNodes(const std::vector<unsigned int>& replaceMeshIndex, aiNode* node)
{


	if (node->mNumMeshes)
	{
		unsigned int newSize = 0;
		for (unsigned int m = 0; m< node->mNumMeshes; ++m)
		{
			unsigned int add = node->mMeshes[m]<<2;
			for (unsigned int i = 0; i < 4;++i)
			{
				if (UINT_MAX != replaceMeshIndex[add+i])++newSize;
			}
		}
		if (!newSize)
		{
			delete[] node->mMeshes;
			node->mNumMeshes = 0;
			node->mMeshes    = NULL;
		}
		else
		{

			unsigned int* newMeshes = (newSize > node->mNumMeshes
				? new unsigned int[newSize] : node->mMeshes);

			for (unsigned int m = 0; m< node->mNumMeshes; ++m)
			{
				unsigned int add = node->mMeshes[m]<<2;
				for (unsigned int i = 0; i < 4;++i)
				{
					if (UINT_MAX != replaceMeshIndex[add+i])
						*newMeshes++ = replaceMeshIndex[add+i];
				}
			}
			if (newSize > node->mNumMeshes)
				delete[] node->mMeshes;

			node->mMeshes = newMeshes-(node->mNumMeshes = newSize);
		}
	}


	for (unsigned int m = 0; m < node->mNumChildren; ++m)
		UpdateNodes(replaceMeshIndex,node->mChildren[m]);
}
