CreateNodes( const Q3BSP::Q3BSPModel *pModel, aiScene* pScene,
									aiNode *pParent )
{
	ai_assert( NULL != pModel );
	if ( NULL == pModel )
	{
		return;
	}

	unsigned int matIdx = 0;
	std::vector<aiMesh*> MeshArray;
	std::vector<aiNode*> NodeArray;
	for ( FaceMapIt it = m_MaterialLookupMap.begin(); it != m_MaterialLookupMap.end(); ++it )
	{
		std::vector<Q3BSP::sQ3BSPFace*> *pArray = (*it).second;
		size_t numVerts = countData( *pArray );
		if ( 0 != numVerts )
		{
			aiMesh* pMesh = new aiMesh;
			aiNode *pNode = CreateTopology( pModel, matIdx, *pArray, pMesh );
			if ( NULL != pNode )
			{
				NodeArray.push_back( pNode );
				MeshArray.push_back( pMesh );
			}
			else
			{
				delete pMesh;
			}
		}
		matIdx++;
	}

	pScene->mNumMeshes = MeshArray.size();
	if ( pScene->mNumMeshes > 0 )
	{
		pScene->mMeshes = new aiMesh*[ pScene->mNumMeshes ];
		for ( size_t i = 0; i < MeshArray.size(); i++ )
		{
			aiMesh *pMesh = MeshArray[ i ];
			if ( NULL != pMesh )
			{
				pScene->mMeshes[ i ] = pMesh;
			}
		}
	}

	pParent->mNumChildren = MeshArray.size();
	pParent->mChildren = new aiNode*[ pScene->mRootNode->mNumChildren ];
	for ( size_t i=0; i<NodeArray.size(); i++ )
	{
		aiNode *pNode = NodeArray[ i ];
		pNode->mParent = pParent;
		pParent->mChildren[ i ] = pNode;
		pParent->mChildren[ i ]->mMeshes[ 0 ] = i;
	}
}
