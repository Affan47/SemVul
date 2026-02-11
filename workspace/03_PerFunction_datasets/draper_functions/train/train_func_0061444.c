popAt(int index){
    if(index>=setOfStacks.size() || index<0)
	return;
    if(index==setOfStacks.size()-1)
	pop();
    else{
	for(unsigned i=index; i<setOfStacks.size()-1; ++i){
	    setOfStacks[i][capacity-1]=setOfStacks[i+1][0];
	    for(unsigned j=1; j<setOfStacks[i+1].size(); ++j)
		setOfStacks[i+1][j-1]=setOfStacks[i+1][j];
	}
	pop();
    }
}
