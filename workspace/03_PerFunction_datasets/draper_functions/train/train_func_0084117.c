createMaterials( const Q3BSP::Q3BSPModel *pModel, aiScene* pScene,
										Q3BSPZipArchive *pArchive )
{
	if ( m_MaterialLookupMap.empty() )
	{
		return;
	}

	pScene->mMaterials = new aiMaterial*[ m_MaterialLookupMap.size() ];
	aiString aiMatName;
	int textureId( -1 ), lightmapId( -1 );
	for ( FaceMapIt it = m_MaterialLookupMap.begin(); it != m_MaterialLookupMap.end();
		++it )
	{
		const std::string matName = (*it).first;
		if ( matName.empty() )
		{
			continue;
		}

		aiMatName.Set( matName );
		aiMaterial *pMatHelper = new aiMaterial;
		pMatHelper->AddProperty( &aiMatName, AI_MATKEY_NAME );

		extractIds( matName, textureId, lightmapId );


		if ( -1 != textureId )
		{
			sQ3BSPTexture *pTexture = pModel->m_Textures[ textureId ];
			if ( NULL != pTexture )
			{
				std::string tmp( "*" ), texName( "" );
				tmp += pTexture->strName;
				tmp += ".jpg";
				normalizePathName( tmp, texName );

				if ( !importTextureFromArchive( pModel, pArchive, pScene, pMatHelper, textureId ) )
				{
				}
			}

		}
		if ( -1 != lightmapId )
		{
			importLightmap( pModel, pScene, pMatHelper, lightmapId );
		}
		pScene->mMaterials[ pScene->mNumMaterials ] = pMatHelper;
		pScene->mNumMaterials++;
	}
	pScene->mNumTextures = mTextures.size();
	pScene->mTextures = new aiTexture*[ pScene->mNumTextures ];
	std::copy( mTextures.begin(), mTextures.end(), pScene->mTextures );
}
