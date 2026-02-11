ReadBRUS(){
	int n_texs=ReadInt();
	if( n_texs<0 || n_texs>8 ){
		Fail( "Bad texture count" );
	}
	while( ChunkSize() ){
		string name=ReadString();
		aiVector3D color=ReadVec3();
		float alpha=ReadFloat();
		float shiny=ReadFloat();
		ReadInt();
		int fx=ReadInt();

		aiMaterial *mat=new aiMaterial;
		_materials.push_back( mat );


		aiString ainame( name );
		mat->AddProperty( &ainame,AI_MATKEY_NAME );


		mat->AddProperty( &color,1,AI_MATKEY_COLOR_DIFFUSE );


		mat->AddProperty( &alpha,1,AI_MATKEY_OPACITY );


		aiColor3D speccolor( shiny,shiny,shiny );
		mat->AddProperty( &speccolor,1,AI_MATKEY_COLOR_SPECULAR );


		float specpow=shiny*128;
		mat->AddProperty( &specpow,1,AI_MATKEY_SHININESS );


		if( fx & 0x10 ){
			int i=1;
			mat->AddProperty( &i,1,AI_MATKEY_TWOSIDED );
		}


		for( int i=0;i<n_texs;++i ){
			int texid=ReadInt();
			if( texid<-1 || (texid>=0 && texid>=static_cast<int>(_textures.size())) ){
				Fail( "Bad texture id" );
			}
			if( i==0 && texid>=0 ){
				aiString texname( _textures[texid] );
				mat->AddProperty( &texname,AI_MATKEY_TEXTURE_DIFFUSE(0) );
			}
		}
	}
}
