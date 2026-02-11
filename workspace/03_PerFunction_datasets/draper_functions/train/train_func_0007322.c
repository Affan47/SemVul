readMaterials(io::IXMLReader* reader, ISceneNode* node)
{
	u32 nr = 0;

	while(reader->read())
	{
		const wchar_t* name = reader->getNodeName();

		switch(reader->getNodeType())
		{
		case io::EXN_ELEMENT_END:
			if (core::stringw(L"materials")==name)
				return;
			break;
		case io::EXN_ELEMENT:
			if (core::stringw(L"attributes")==name)
			{

				io::IAttributes* attr = FileSystem->createEmptyAttributes(Driver);
				attr->read(reader);

				if (node && node->getMaterialCount() > nr)
				{
					getVideoDriver()->fillMaterialStructureFromAttributes(
						node->getMaterial(nr), attr);
				}

				attr->drop();
				++nr;
			}
			break;
		default:
			break;
		}
	}
}
