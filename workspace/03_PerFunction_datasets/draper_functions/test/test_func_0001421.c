index_of(XMLCh ch) {
	if(ch==' ') return STRING_NOT_FOUND;
	return fletter2index.get(ch);
}
