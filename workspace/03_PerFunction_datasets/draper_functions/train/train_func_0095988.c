CreateDataRepresentationFromImport( aiScene* pScene, XFile::Scene* pData)
{

	ConvertMaterials( pScene, pData->mGlobalMaterials);


	pScene->mRootNode = CreateNodes( pScene, NULL, pData->mRootNode);


	CreateAnimations( pScene, pData);


	if( pData->mGlobalMeshes.size() > 0)
	{

		if( pScene->mRootNode == NULL)
		{
			pScene->mRootNode = new aiNode;
			pScene->mRootNode->mName.Set( "$dummy_node");
		}


		CreateMeshes( pScene, pScene->mRootNode, pData->mGlobalMeshes);
	}


	MakeLeftHandedProcess convertProcess;
	convertProcess.Execute( pScene);

	FlipWindingOrderProcess flipper;
	flipper.Execute(pScene);


	if( pScene->mNumMaterials == 0)
	{
		pScene->mNumMaterials = 1;

		aiMaterial* mat = new aiMaterial;
		int shadeMode = (int) aiShadingMode_Gouraud;
		mat->AddProperty<int>( &shadeMode, 1, AI_MATKEY_SHADING_MODEL);

		int specExp = 1;

		aiColor3D clr = aiColor3D( 0, 0, 0);
		mat->AddProperty( &clr, 1, AI_MATKEY_COLOR_EMISSIVE);
		mat->AddProperty( &clr, 1, AI_MATKEY_COLOR_SPECULAR);

		clr = aiColor3D( 0.5f, 0.5f, 0.5f);
		mat->AddProperty( &clr, 1, AI_MATKEY_COLOR_DIFFUSE);
		mat->AddProperty( &specExp, 1, AI_MATKEY_SHININESS);

		pScene->mMaterials = new aiMaterial*[1];
		pScene->mMaterials[0] = mat;
	}
}
