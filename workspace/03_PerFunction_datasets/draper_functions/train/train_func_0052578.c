GetMeshVFormat(aiMesh* pcMesh)
{


	if (pcMesh->mBones)
		return (unsigned int)(uint64_t)pcMesh->mBones;


	const unsigned int iRet = GetMeshVFormatUnique(pcMesh);


	pcMesh->mBones = (aiBone**)(uint64_t)iRet;
	return iRet;
}
