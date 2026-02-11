ReadLght_Binary(COB::Scene& out, StreamReaderLE& reader, const ChunkInfo& nfo)
{
	if(nfo.version > 2) {
		return UnsupportedChunk_Binary(reader,nfo,"Lght");
	}

	const chunk_guard cn(nfo,reader);

	out.nodes.push_back(boost::shared_ptr<Light>(new Light()));
	Light& msh = (Light&)(*out.nodes.back().get());
	msh = nfo;

	ReadBasicNodeInfo_Binary(msh,reader,nfo);
}
