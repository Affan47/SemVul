LoadGeometrySource(FCDObject* object, xmlNode* sourceNode)
{
	FCDGeometrySource* geometrySource = (FCDGeometrySource*) object;
	FCDGeometrySourceData data;
	data.sourceNode = sourceNode;
	FArchiveXML::documentLinkDataMap[geometrySource->GetDocument()].geometrySourceDataMap.insert(geometrySource, data);

	bool status = true;


	geometrySource->SetName(TO_FSTRING(ReadNodeName(sourceNode)));
	fm::string id = ReadNodeId(sourceNode);
	if (id.empty())
	{
		FUError::Error(FUError::WARNING_LEVEL, FUError::WARNING_INVALID_GEOMETRY_SOURCE_ID, sourceNode->line);
	}
	geometrySource->SetDaeId(id);
	if (!id.empty() && geometrySource->GetDaeId() != id)
	{
		FUError::Error(FUError::ERROR_LEVEL, FUError::ERROR_DUPLICATE_ID, sourceNode->line);
	}


	geometrySource->SetStride(ReadSource(sourceNode, geometrySource->GetSourceData().GetDataList()));
	if (geometrySource->GetStride() == 0)
	{
		FUError::Error(FUError::WARNING_LEVEL, FUError::WARNING_EMPTY_SOURCE, sourceNode->line);
	}


	FCDExtra* extra = geometrySource->GetExtra();
	FArchiveXML::LoadExtra(extra, sourceNode);
	if (extra->GetDefaultType()->GetTechniqueCount() == 0) SAFE_RELEASE(extra)

	return status;
}
