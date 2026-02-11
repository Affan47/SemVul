InternReadFile_HMP7( )
{

	const HMP::Header_HMP5* const pcHeader = (const HMP::Header_HMP5*)mBuffer;
	const unsigned char* szCurrent = (const unsigned char*)(mBuffer+84);
	ValidateHeader_HMP457();


	pScene->mNumMeshes = 1;
	pScene->mMeshes = new aiMesh*[1];
	aiMesh* pcMesh = pScene->mMeshes[0] = new aiMesh();

	pcMesh->mMaterialIndex = 0;
	pcMesh->mVertices = new aiVector3D[pcHeader->numverts];
	pcMesh->mNormals = new aiVector3D[pcHeader->numverts];

	const unsigned int height = (unsigned int)(pcHeader->numverts / pcHeader->fnumverts_x);
	const unsigned int width = (unsigned int)pcHeader->fnumverts_x;


	CreateMaterial(szCurrent,&szCurrent);


	szCurrent += 36;

	SizeCheck(szCurrent + sizeof(const HMP::Vertex_HMP7)*height*width);


	aiVector3D* pcVertOut = pcMesh->mVertices;
	aiVector3D* pcNorOut = pcMesh->mNormals;
	const HMP::Vertex_HMP7* src = (const HMP::Vertex_HMP7*) szCurrent;
	for (unsigned int y = 0; y < height;++y)
	{
		for (unsigned int x = 0; x < width;++x)
		{
			pcVertOut->x = x * pcHeader->ftrisize_x;
			pcVertOut->y = y * pcHeader->ftrisize_y;


			pcVertOut->z = (((float)src->z / 0xffff)-0.5f) * pcHeader->ftrisize_x * 8.0f;

			pcNorOut->x = ((float)src->normal_x / 0x80 );
			pcNorOut->y = ((float)src->normal_y / 0x80 );
			pcNorOut->z = 1.0f;
			pcNorOut->Normalize();

			++pcVertOut;++pcNorOut;++src;
		}
	}


	if (pcHeader->numskins)GenerateTextureCoords(width,height);


	CreateOutputFaceList(width,height);


	pScene->mRootNode = new aiNode();
	pScene->mRootNode->mName.Set("terrain_root");
	pScene->mRootNode->mNumMeshes = 1;
	pScene->mRootNode->mMeshes = new unsigned int[1];
	pScene->mRootNode->mMeshes[0] = 0;
}
