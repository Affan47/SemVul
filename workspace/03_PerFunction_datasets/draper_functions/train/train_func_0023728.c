checkValid(int currPos, const vector<int> &preInput){
    for(size_t j=0; j<preInput.size(); ++j){
	if(currPos==preInput[j]||(currPos-preInput[j]==preInput.size()-j) || (currPos-preInput[j]==j-preInput.size()))
	    return false;
    }
    return true;
}
