AddSourceTexcoord(xmlNode* parent, const char* id, const FMVector3List& values)
	{
		xmlNode* sourceNode = AddChild(parent, DAE_SOURCE_ELEMENT);
		AddAttribute(sourceNode, DAE_ID_ATTRIBUTE, id);
		FUSStringBuilder arrayId(id); arrayId.append("-array");
		AddArray(sourceNode, arrayId.ToCharPtr(), values);
		xmlNode* techniqueCommonNode = AddChild(sourceNode, DAE_TECHNIQUE_COMMON_ELEMENT);
		AddAccessor(techniqueCommonNode, arrayId.ToCharPtr(), values.size(), 3, FUDaeAccessor::STPQ, DAE_FLOAT_TYPE);
		return sourceNode;
	}
