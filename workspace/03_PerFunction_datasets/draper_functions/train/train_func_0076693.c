aiExportSceneToBlob( const aiScene* pScene, const char* pFormatId, unsigned int pPreprocessing  )
{
	Exporter exp;
	if (!exp.ExportToBlob(pScene,pFormatId,pPreprocessing)) {
		return NULL;
	}
	const aiExportDataBlob* blob = exp.GetOrphanedBlob();
	ai_assert(blob);

	return blob;
}
