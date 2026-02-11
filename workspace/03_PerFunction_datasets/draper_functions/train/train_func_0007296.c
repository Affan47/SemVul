CountNodes( aiNode* pcNode )
{
	unsigned int iRet = 1;
	for (unsigned int i = 0;i < pcNode->mNumChildren;++i)
	{
		iRet += CountNodes(pcNode->mChildren[i]);
	}
	return iRet;
}
