transferLeft(){
    while(!stackInput.empty()){
	int temp = stackInput.back();
	stackOutput.push_back(temp);
	stackInput.pop_back();
    }
}
