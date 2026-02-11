AddNodeWeight(unsigned int& iScene,const aiNode* pcNode)
{
	iScene += sizeof(aiNode);
	iScene += sizeof(unsigned int) * pcNode->mNumMeshes;
	iScene += sizeof(void*) * pcNode->mNumChildren;

	for (unsigned int i = 0; i < pcNode->mNumChildren;++i) {
		AddNodeWeight(iScene,pcNode->mChildren[i]);
	}
}
