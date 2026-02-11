DelArrayEntry( gnSeqC *array[GNSEQC_MAX], const gnSeqC ch, const gnSeqC ch2){

	gnSeqC* loc = strchr(m_containArray[ch], ch2);
	uint32 count = 0;
	while(loc != NULL){
		count++;
		loc = strchr(loc+1, ch2);
	}
	if(count == 0)
		return;

	uint32 curlen = strlen(array[ch]);
	gnSeqC* tmp = new gnSeqC[curlen - count];
	uint32 tmppos = 0;
	for(uint32 i=0; i < curlen; i++)
		if(m_containArray[ch][i] != ch2)
			tmp[tmppos++] = m_containArray[ch][i];
	tmp[tmppos] = 0;
	delete[] array[ch];
	array[ch] = tmp;
}
