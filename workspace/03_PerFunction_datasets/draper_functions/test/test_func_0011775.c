addRule(FuzzyRule rule){
	if (indexRule < MAX_NUMBER_OF_RULES){
		baseRules[indexRule] = rule;
		indexRule = indexRule + 1;
	}


        reOrderBaseRules();
}
