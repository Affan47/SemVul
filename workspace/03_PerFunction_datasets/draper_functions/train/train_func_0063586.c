AddMeshes(const ASE::BaseNode* snode,aiNode* node)
{
	for (unsigned int i = 0; i < pcScene->mNumMeshes;++i)	{

		const aiMesh* pcMesh  = pcScene->mMeshes[i];
		const ASE::Mesh* mesh = (const ASE::Mesh*)pcMesh->mColors[2];

		if (mesh == snode) {
			++node->mNumMeshes;
		}
	}

	if(node->mNumMeshes)	{
		node->mMeshes = new unsigned int[node->mNumMeshes];
		for (unsigned int i = 0, p = 0; i < pcScene->mNumMeshes;++i)	{

			const aiMesh* pcMesh  = pcScene->mMeshes[i];
			const ASE::Mesh* mesh = (const ASE::Mesh*)pcMesh->mColors[2];
			if (mesh == snode)	{
				node->mMeshes[p++] = i;


				aiMatrix4x4 m  = mesh->mTransform;
				m.Inverse();

				aiVector3D* pvCurPtr = pcMesh->mVertices;
				const aiVector3D* pvEndPtr = pvCurPtr + pcMesh->mNumVertices;
				while (pvCurPtr != pvEndPtr)	{
					*pvCurPtr = m * (*pvCurPtr);
					pvCurPtr++;
				}


				if (pcMesh->mNormals)	{
					aiMatrix3x3 m3 = aiMatrix3x3( mesh->mTransform );
					m3.Transpose();

					pvCurPtr = pcMesh->mNormals;
					pvEndPtr = pvCurPtr + pcMesh->mNumVertices;
					while (pvCurPtr != pvEndPtr)	{
						*pvCurPtr = m3 * (*pvCurPtr);
						pvCurPtr++;
					}
				}
			}
		}
	}
}
