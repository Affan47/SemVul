getHits(vector<int> &charNumArray, string &guessStr, const string &correctStr){
    int count = 0;
    for(size_t i=0; i<min(guessStr.size(), correctStr.size()); ++i){
	if(guessStr[i]==correctStr[i]){
	    ++count;
	    --charNumArray[getIndex(guessStr[i])];
	    guessStr[i] = '0';
	}
    }
    return count;
}
