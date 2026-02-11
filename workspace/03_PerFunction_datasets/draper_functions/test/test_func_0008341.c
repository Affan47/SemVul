makeNewStack(){

	struct stack* stc = (struct stack*)gcMalloc(sizeof(struct stack));
	if(stc == NULL){
		Log("Allocation error", ERROR, STACK);
		exit(intern);
	}


	stc->Top = NULL;
	stc->Length = 0;
	return stc;
}
