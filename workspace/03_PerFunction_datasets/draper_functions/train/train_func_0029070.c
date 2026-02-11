CopyMaterial(std::vector<aiMaterial*>& materials,
	std::vector< std::pair<aiMaterial*, unsigned int> >& inmaterials,
	unsigned int& defMatIdx,
	aiMesh* mesh)
{
	if (inmaterials.empty())	{

		if (UINT_MAX == defMatIdx)
		{
			defMatIdx = (unsigned int)materials.size();
			aiMaterial* mat = new aiMaterial();

			aiString s;
			s.Set(AI_DEFAULT_MATERIAL_NAME);
			mat->AddProperty(&s,AI_MATKEY_NAME);

			aiColor3D c(0.6f,0.6f,0.6f);
			mat->AddProperty(&c,1,AI_MATKEY_COLOR_DIFFUSE);
		}
		mesh->mMaterialIndex = defMatIdx;
		return;
	}
	else if (inmaterials.size() > 1)	{
		DefaultLogger::get()->info("IRR: Skipping additional materials");
	}

	mesh->mMaterialIndex = (unsigned int)materials.size();
	materials.push_back(inmaterials[0].first);
}
