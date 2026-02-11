writeVertices(std::fstream & fs, const std::vector<float*> & vertexAttributes, const GeometryInfo & info)
{
	uint32_t i = 0;
	for (std::vector<uint32_t>::const_iterator it=info.attributeSemantics.begin(); it!=info.attributeSemantics.end(); ++it)
	{
		fs.write((char*)vertexAttributes.at(i), info.numberVertices * floats(*it) * sizeof(float));
		++i;
	}
}
