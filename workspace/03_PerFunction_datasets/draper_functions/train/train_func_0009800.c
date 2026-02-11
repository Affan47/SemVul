BuildSingleQuadMesh(const SkyboxVertex& v1,
	const SkyboxVertex& v2,
	const SkyboxVertex& v3,
	const SkyboxVertex& v4)
{

	aiMesh* out = new aiMesh();

	out->mPrimitiveTypes = aiPrimitiveType_POLYGON;
	out->mNumFaces = 1;


	out->mFaces    = new aiFace[1];
	aiFace& face   = out->mFaces[0];

	face.mNumIndices = 4;
	face.mIndices    = new unsigned int[4];
	for (unsigned int i = 0; i < 4;++i)
		face.mIndices[i] = i;

	out->mNumVertices = 4;


	aiVector3D* vec = out->mVertices = new aiVector3D[4];
	*vec++ = v1.position;
	*vec++ = v2.position;
	*vec++ = v3.position;
	*vec   = v4.position;


	vec = out->mNormals = new aiVector3D[4];
	*vec++ = v1.normal;
	*vec++ = v2.normal;
	*vec++ = v3.normal;
	*vec   = v4.normal;


	vec = out->mTextureCoords[0] = new aiVector3D[4];
	*vec++ = v1.uv;
	*vec++ = v2.uv;
	*vec++ = v3.uv;
	*vec   = v4.uv;
	return out;
}
