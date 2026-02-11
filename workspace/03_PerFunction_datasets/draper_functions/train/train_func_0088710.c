checkCombination(const string &str, bool flag, const set<string> &strSet){
    if(flag==false && strSet.find(str)!=strSet.end())
	return true;
    if(str.empty())
	return false;
    for(size_t i=1; i!=str.size(); ++i){
	if(strSet.find(string(str.begin(), str.begin()+i))!=strSet.end()){
	    bool resultSecond = checkCombination(string(str.begin()+i, str.end()), false, strSet);
	    if(resultSecond)
		return true;
	}
    }
    return false;
}
