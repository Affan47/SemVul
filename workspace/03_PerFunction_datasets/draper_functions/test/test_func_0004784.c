UpdateNode(aiNode* pcNode,
	const std::vector<std::pair<aiMesh*, unsigned int> >& avList)
{

	std::vector<unsigned int> aiEntries;
	aiEntries.reserve(pcNode->mNumMeshes + 1);
	for (unsigned int i = 0; i < pcNode->mNumMeshes;++i)
	{
		for (unsigned int a = 0; a < avList.size();++a)
		{
			if (avList[a].second == pcNode->mMeshes[i])
			{
				aiEntries.push_back(a);
			}
		}
	}


	delete pcNode->mMeshes;
	pcNode->mNumMeshes = (unsigned int)aiEntries.size();
	pcNode->mMeshes = new unsigned int[pcNode->mNumMeshes];

	for (unsigned int b = 0; b < pcNode->mNumMeshes;++b)
		pcNode->mMeshes[b] = aiEntries[b];


	for (unsigned int i = 0; i < pcNode->mNumChildren;++i)
	{
		UpdateNode ( pcNode->mChildren[i], avList );
	}
	return;
}
