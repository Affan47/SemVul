DisCompile(void) const{
	string retstr;
	for (TCodePVector::const_iterator it=list.begin(); it!=list.end(); it++){
		retstr+=(*it)->DisCompile();
	}
	return retstr;
}
