Filter( gnSeqC** seq, gnSeqI& len ) const{
	uint32 curpos = 0;
	string output;
	while(curpos < len){
		uint32 i=0;
		for(; i < m_inputTable.size(); i++){

			uint32 curlen = m_inputTable[i].length();
			if(len - curpos < curlen)
				continue;
			if(compare->Contains(m_inputTable[i].data(), *seq + curpos, curlen)){
				output += m_outputTable[i];
				curpos += curlen;
				break;
			}
		}
		if(i == m_inputTable.size()){

			if(use_default)
				output += m_defaultChar;
			curpos += m_defaultInputWidth;
		}
	}
	if(output.length() > len){
		delete[] *seq;
		*seq = new gnSeqC[output.length()];
	}
	len = output.length();
	memcpy(*seq, output.data(), len);
}
