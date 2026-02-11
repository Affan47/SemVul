WriteMaterialFile()
{
	WriteHeader(mOutputMat);

	for(unsigned int i = 0; i < pScene->mNumMaterials; ++i) {
		const aiMaterial* const mat = pScene->mMaterials[i];

		int illum = 1;
		mOutputMat << "newmtl " << GetMaterialName(i)  << endl;

		aiColor4D c;
		if(AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_DIFFUSE,c)) {
			mOutputMat << "kd " << c.r << " " << c.g << " " << c.b << endl;
		}
		if(AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_AMBIENT,c)) {
			mOutputMat << "ka " << c.r << " " << c.g << " " << c.b << endl;
		}
		if(AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_SPECULAR,c)) {
			mOutputMat << "ks " << c.r << " " << c.g << " " << c.b << endl;
		}
		if(AI_SUCCESS == mat->Get(AI_MATKEY_COLOR_EMISSIVE,c)) {
			mOutputMat << "ke " << c.r << " " << c.g << " " << c.b << endl;
		}

		float o;
		if(AI_SUCCESS == mat->Get(AI_MATKEY_OPACITY,o)) {
			mOutputMat << "d " << o << endl;
		}

		if(AI_SUCCESS == mat->Get(AI_MATKEY_SHININESS,o) && o) {
			mOutputMat << "Ns " << o << endl;
			illum = 2;
		}

		mOutputMat << "illum " << illum << endl;

		aiString s;
		if(AI_SUCCESS == mat->Get(AI_MATKEY_TEXTURE_DIFFUSE(0),s)) {
			mOutputMat << "map_kd " << s.data << endl;
		}
		if(AI_SUCCESS == mat->Get(AI_MATKEY_TEXTURE_AMBIENT(0),s)) {
			mOutputMat << "map_ka " << s.data << endl;
		}
		if(AI_SUCCESS == mat->Get(AI_MATKEY_TEXTURE_SPECULAR(0),s)) {
			mOutputMat << "map_ks " << s.data << endl;
		}
		if(AI_SUCCESS == mat->Get(AI_MATKEY_TEXTURE_SHININESS(0),s)) {
			mOutputMat << "map_ns " << s.data << endl;
		}
		if(AI_SUCCESS == mat->Get(AI_MATKEY_TEXTURE_HEIGHT(0),s) || AI_SUCCESS == mat->Get(AI_MATKEY_TEXTURE_NORMALS(0),s)) {

			mOutputMat << "bump " << s.data << endl;
			mOutputMat << "map_bump " << s.data << endl;
		}

		mOutputMat << endl;
	}
}
