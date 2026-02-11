ReplaceDefaultMaterial(std::vector<PLY::Face>* avFaces,
	std::vector<aiMaterial*>* avMaterials)
{
	bool bNeedDefaultMat = false;

	for (std::vector<PLY::Face>::iterator i =  avFaces->begin();i != avFaces->end();++i)	{
		if (0xFFFFFFFF == (*i).iMaterialIndex)	{
			bNeedDefaultMat = true;
			(*i).iMaterialIndex = (unsigned int)avMaterials->size();
		}
		else if ((*i).iMaterialIndex >= avMaterials->size() )	{

			(*i).iMaterialIndex = (unsigned int)avMaterials->size()-1;
		}
	}

	if (bNeedDefaultMat)	{

		aiMaterial* pcHelper = new aiMaterial();


		int iMode = (int)aiShadingMode_Gouraud;
		pcHelper->AddProperty<int>(&iMode, 1, AI_MATKEY_SHADING_MODEL);

		aiColor3D clr;
		clr.b = clr.g = clr.r = 0.6f;
		pcHelper->AddProperty<aiColor3D>(&clr, 1,AI_MATKEY_COLOR_DIFFUSE);
		pcHelper->AddProperty<aiColor3D>(&clr, 1,AI_MATKEY_COLOR_SPECULAR);

		clr.b = clr.g = clr.r = 0.05f;
		pcHelper->AddProperty<aiColor3D>(&clr, 1,AI_MATKEY_COLOR_AMBIENT);


		const int two_sided = 1;
		pcHelper->AddProperty(&two_sided,1,AI_MATKEY_TWOSIDED);

		avMaterials->push_back(pcHelper);
	}
}
