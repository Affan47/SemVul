getContainedChunks(const RegionIdx& ri, const string& filename)
{
	vector<ChunkIdx> chunks;
	RegionFile regfile;
	if (0 != regfile.loadHeaderOnly(filename))
		return chunks;
	for (RegionChunkIterator it(ri); !it.end; it.advance())
		if (regfile.containsChunk(it.current))
			chunks.push_back(it.current);
	return chunks;
}
