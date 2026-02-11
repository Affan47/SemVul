aiApplyPostProcessing(const aiScene* pScene,
	unsigned int pFlags)
{
	const aiScene* sc = NULL;


	ASSIMP_BEGIN_EXCEPTION_REGION();


	const ScenePrivateData* priv = ScenePriv(pScene);
	if( !priv || !priv->mOrigImporter)	{
		ReportSceneNotFoundError();
		return NULL;
	}

	sc = priv->mOrigImporter->ApplyPostProcessing(pFlags);

	if (!sc) {
		aiReleaseImport(pScene);
		return NULL;
	}

	ASSIMP_END_EXCEPTION_REGION(const aiScene*);
	return sc;
}
