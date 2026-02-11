RemoveVertexSource(FCDGeometrySource* source)
{
	FUAssert(source != NULL, return);
	if (!vertexSources.contains(source)) return;


	vertexSources.erase(source);
	SetDirtyFlag();
}
