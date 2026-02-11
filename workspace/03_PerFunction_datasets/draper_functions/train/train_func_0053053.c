removeFromGenRoot(Object* object){
	int i;
	for(i = 0 ; (unsigned int) i<remSet.size() ; i++){
		if(remSet.at(i) == object){
			remSet.at(i) = NULL;
			remCount--;
			return 0;
		}
	}
	return -1;
}
