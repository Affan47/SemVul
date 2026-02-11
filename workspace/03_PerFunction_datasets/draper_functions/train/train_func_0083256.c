readMaterial(io::IXMLReaderUTF8* reader)
{
	#ifdef COLLADA_READER_DEBUG
	os::Printer::log("COLLADA reading material");
	#endif


	Materials.push_back(SColladaMaterial());

	SColladaMaterial& material = Materials.getLast();
	material.Id = readId(reader);

	if (Version >= 10400)
	{
		while(reader->read())
		{
			if (reader->getNodeType() == io::EXN_ELEMENT &&
				instanceEffectName == reader->getNodeName())
			{
				material.InstanceEffectId = reader->getAttributeValue("url");
				uriToId(material.InstanceEffectId);
			}
			else
			if (reader->getNodeType() == io::EXN_ELEMENT_END &&
				materialSectionName == reader->getNodeName())
			{
				break;
			}
		}
	}
	else
	{
		if (!reader->isEmptyElement())
		{
			readColladaInputs(reader, materialSectionName);
			SColladaInput* input = getColladaInput(ECIS_TEXTURE);
			if (input)
			{
				core::stringc textureName = input->Source;
				uriToId(textureName);
				for (u32 i=0; i<Textures.size(); ++i)
					if (textureName == Textures[i].Id)
					{
						material.Mat.setTexture(0, Textures[i].Texture);
						break;
					}
			}


#if 0
			readColladaParameters(reader, materialSectionName);

			SColladaParam* p;

			p = getColladaParameter(ECPN_AMBIENT);
			if (p && p->Type == ECPT_FLOAT3)
				material.Mat.AmbientColor = video::SColorf(p->Floats[0],p->Floats[1],p->Floats[2]).toSColor();
			p = getColladaParameter(ECPN_DIFFUSE);
			if (p && p->Type == ECPT_FLOAT3)
				material.Mat.DiffuseColor = video::SColorf(p->Floats[0],p->Floats[1],p->Floats[2]).toSColor();
			p = getColladaParameter(ECPN_SPECULAR);
			if (p && p->Type == ECPT_FLOAT3)
				material.Mat.DiffuseColor = video::SColorf(p->Floats[0],p->Floats[1],p->Floats[2]).toSColor();
			p = getColladaParameter(ECPN_SHININESS);
			if (p && p->Type == ECPT_FLOAT)
				material.Mat.Shininess = p->Floats[0];
#endif
		}
	}
}
