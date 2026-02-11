write(const std::string & file, const GeometrySoA * const geometry, const uint32_t vertexType)
{
	std::fstream fs;
	fs.open(file.c_str(), std::fstream::out | std::fstream::binary | std::fstream::trunc);

	if (fs.is_open())
	{
		if (vertexType == SoA)
		{
			writeHeader(fs, geometry->info);
			writeContent(fs, *geometry);
		}
		else if (vertexType == AoS)
		{
			writeHeader(fs, geometry->info, &vertexType);
			writeIndices(fs, geometry->indices, geometry->info);
			float * vertices = NULL;
			convertVertices(geometry->vertexAttributes, vertices, geometry->info);
			writeVertices(fs, vertices, geometry->info);
			cleanVertices(vertices);
		}
		fs.close();
	}
}
