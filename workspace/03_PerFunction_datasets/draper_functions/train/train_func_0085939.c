readFace(const SPLYElement &Element, scene::CDynamicMeshBuffer* mb)
{
	if (!IsBinaryFile)
		getNextLine();

	for (u32 i=0; i < Element.Properties.size(); ++i)
	{
		if ( (Element.Properties[i].Name == "vertex_indices" ||
			  Element.Properties[i].Name == "vertex_index") && Element.Properties[i].Type == EPLYPT_LIST)
		{

			s32 count = getInt(Element.Properties[i].Data.List.CountType);
			u32 a = getInt(Element.Properties[i].Data.List.ItemType),
				b = getInt(Element.Properties[i].Data.List.ItemType),
				c = getInt(Element.Properties[i].Data.List.ItemType);
			s32 j = 3;

			mb->getIndexBuffer().push_back(a);
			mb->getIndexBuffer().push_back(c);
			mb->getIndexBuffer().push_back(b);

			for (; j < count; ++j)
			{
				b = c;
				c = getInt(Element.Properties[i].Data.List.ItemType);
				mb->getIndexBuffer().push_back(a);
				mb->getIndexBuffer().push_back(c);
				mb->getIndexBuffer().push_back(b);
			}
		}
		else if (Element.Properties[i].Name == "intensity")
		{

			skipProperty(Element.Properties[i]);
		}
		else
			skipProperty(Element.Properties[i]);
	}
	return true;
}
