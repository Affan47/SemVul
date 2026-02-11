importTextureFromArchive( const Q3BSP::Q3BSPModel *pModel,
												 Q3BSP::Q3BSPZipArchive *pArchive, aiScene*,
												 aiMaterial *pMatHelper, int textureId ) {
	if ( NULL == pArchive || NULL == pArchive || NULL == pMatHelper ) {
		return false;
	}

	if ( textureId < 0 || textureId >= static_cast<int>( pModel->m_Textures.size() ) ) {
		return false;
	}

	bool res = true;
	sQ3BSPTexture *pTexture = pModel->m_Textures[ textureId ];
	if ( !pTexture ) {
        return false;
    }

    std::vector<std::string> supportedExtensions;
    supportedExtensions.push_back( ".jpg" );
    supportedExtensions.push_back( ".png" );
    supportedExtensions.push_back( ".tga" );
	std::string textureName, ext;
	if ( expandFile( pArchive, pTexture->strName, supportedExtensions, textureName, ext ) ) {
		IOStream *pTextureStream = pArchive->Open( textureName.c_str() );
		if ( !pTextureStream ) {
			size_t texSize = pTextureStream->FileSize();
			aiTexture *pTexture = new aiTexture;
			pTexture->mHeight = 0;
			pTexture->mWidth = texSize;
			unsigned char *pData = new unsigned char[ pTexture->mWidth ];
			size_t readSize = pTextureStream->Read( pData, sizeof( unsigned char ), pTexture->mWidth );
			(void)readSize;
			ai_assert( readSize == pTexture->mWidth );
			pTexture->pcData = reinterpret_cast<aiTexel*>( pData );
			pTexture->achFormatHint[ 0 ] = ext[ 1 ];
			pTexture->achFormatHint[ 1 ] = ext[ 2 ];
			pTexture->achFormatHint[ 2 ] = ext[ 3 ];
			pTexture->achFormatHint[ 3 ] = '\0';
			res = true;

			aiString name;
			name.data[ 0 ] = '*';
			name.length = 1 + ASSIMP_itoa10( name.data + 1, MAXLEN-1, mTextures.size() );

			pArchive->Close( pTextureStream );

			pMatHelper->AddProperty( &name, AI_MATKEY_TEXTURE_DIFFUSE( 0 ) );
			mTextures.push_back( pTexture );
		} else {


			aiString name;
			strncpy( name.data, pTexture->strName, sizeof name.data );
			name.length = strlen( name.data );
			pMatHelper->AddProperty( &name, AI_MATKEY_TEXTURE_DIFFUSE( 0 ) );
		}
	}

	return res;
}
