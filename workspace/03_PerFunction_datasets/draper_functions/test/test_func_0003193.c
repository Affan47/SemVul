init(){

	for (int i = 0; i < MAX_NUMBER_OF_INPUTS+1; i++){
		inputs[i] = 0;
		for (int k = 0; k < MAX_NUMBER_OF_FUZZY_SETS; k++){
			resultFuzzyfication[i][k] = 0;
			fuzzySetsInput[i][k] = 0;
		}
	}
}
