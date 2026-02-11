Execute( aiScene* pScene)
{
	DefaultLogger::get()->debug("TriangulateProcess begin");

	bool bHas = false;
	for( unsigned int a = 0; a < pScene->mNumMeshes; a++)
	{
		if(	TriangulateMesh( pScene->mMeshes[a]))
			bHas = true;
	}
	if (bHas)DefaultLogger::get()->info ("TriangulateProcess finished. All polygons have been triangulated.");
	else     DefaultLogger::get()->debug("TriangulateProcess finished. There was nothing to be done.");
}
