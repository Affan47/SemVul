stackPop(struct stack* stack){

	if(stack == NULL){
		Log("stackPop: Stack == NULL", ERROR, STACK);
		exit(intern);
	}

	if(stack->Top != NULL){

		struct stackItem* item = stack->Top;
		stack->Top = stack->Top->Next;

		void* val = item->Value;

		gcFree(item);

		stack->Length--;

		return val;
	}
	else {
		Log("stackPop: Stack is empty...", WARNING, STACK);
		return NULL;
	}
}
