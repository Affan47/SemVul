AddTexture ( aiMaterial& mat, const ColladaParser& pParser,
	const Collada::Effect& effect,
	const Collada::Sampler& sampler,
	aiTextureType type, unsigned int idx)
{

	const aiString name = FindFilenameForEffectTexture( pParser, effect, sampler.mName );
	mat.AddProperty( &name, _AI_MATKEY_TEXTURE_BASE, type, idx );


	int map = aiTextureMapMode_Clamp;
	if (sampler.mWrapU)
		map = aiTextureMapMode_Wrap;
	if (sampler.mWrapU && sampler.mMirrorU)
		map = aiTextureMapMode_Mirror;

	mat.AddProperty( &map, 1, _AI_MATKEY_MAPPINGMODE_U_BASE, type, idx);

	map = aiTextureMapMode_Clamp;
	if (sampler.mWrapV)
		map = aiTextureMapMode_Wrap;
	if (sampler.mWrapV && sampler.mMirrorV)
		map = aiTextureMapMode_Mirror;

	mat.AddProperty( &map, 1, _AI_MATKEY_MAPPINGMODE_V_BASE, type, idx);


	mat.AddProperty(&sampler.mTransform, 1,
		_AI_MATKEY_UVTRANSFORM_BASE, type, idx);


	mat.AddProperty((int*)&sampler.mOp , 1,
		_AI_MATKEY_TEXBLEND_BASE, type, idx);


	mat.AddProperty((float*)&sampler.mWeighting , 1,
		_AI_MATKEY_TEXBLEND_BASE, type, idx);


	if (sampler.mUVId != UINT_MAX)
		map = sampler.mUVId;
	else {
		map = -1;
		for (std::string::const_iterator it = sampler.mUVChannel.begin();it != sampler.mUVChannel.end(); ++it){
			if (IsNumeric(*it)) {
				map = strtoul10(&(*it));
				break;
			}
		}
		if (-1 == map) {
			DefaultLogger::get()->warn("Collada: unable to determine UV channel for texture");
			map = 0;
		}
	}
	mat.AddProperty(&map,1,_AI_MATKEY_UVWSRC_BASE,type,idx);
}
