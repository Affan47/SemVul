aiGetMemoryRequirements(const C_STRUCT aiScene* pIn,
	C_STRUCT aiMemoryInfo* in)
{
	ASSIMP_BEGIN_EXCEPTION_REGION();


	const ScenePrivateData* priv = ScenePriv(pIn);
	if( !priv || !priv->mOrigImporter)	{
		ReportSceneNotFoundError();
		return;
	}

	return priv->mOrigImporter->GetMemoryRequirements(*in);
	ASSIMP_END_EXCEPTION_REGION(void);
}
