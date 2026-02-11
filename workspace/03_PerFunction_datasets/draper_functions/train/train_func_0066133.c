Write(gnBaseSource *source, const string& filename){
	ofstream m_ofstream(filename.c_str(), ios::out | ios::binary);
	if(!m_ofstream.is_open())
		return false;
	uint32 contigCount = source->GetContigListLength();
	for(uint32 contigI = 0; contigI < contigCount; contigI++){
		string contigName = source->GetContigName(contigI);
		m_ofstream << ">" << contigName << ";\n";
		gnSeqI seqLength = source->GetContigSeqLength(contigI);
		while(seqLength > 0){
			gnSeqI writeLen = seqLength < BUFFER_SIZE ? seqLength : BUFFER_SIZE;
			Array<gnSeqC> array_buf( writeLen+1 );
			gnSeqC *bases = array_buf.data;
			boolean success = source->SeqRead(0, bases, writeLen, contigI);
			if(!success)
				return false;
			bases[writeLen] = 0;
			m_ofstream << bases << "\n";
			seqLength -= writeLen;
		}
	}
	m_ofstream.close();
	return true;
}
