Levels_new(IoMessage *msg)
{
	Levels *self = io_calloc(1, sizeof(Levels));

	IoState *state = IoObject_state(msg);
	IoSymbol *operatorTableSymbol = IoState_symbolWithCString_(state, "OperatorTable");


	IoObject *opTable = IoObject_rawGetSlot_(msg, operatorTableSymbol);


	if (opTable == NULL)
	{


		opTable = IoObject_rawGetSlot_(state->core, operatorTableSymbol);


		if (opTable == NULL)
		{
			opTable = IoObject_new(state);
			IoObject_setSlot_to_(state->core, operatorTableSymbol, opTable);
			IoObject_setSlot_to_(opTable, IoState_symbolWithCString_(state, "precedenceLevelCount"), IoState_numberWithDouble_(state, IO_OP_MAX_LEVEL));
		}
	}

	self->operatorTable = getOpTable(opTable, "operators", IoState_createOperatorTable);
	self->assignOperatorTable = getOpTable(opTable, "assignOperators", IoState_createAssignOperatorTable);

	self->stack = List_new();
	Levels_reset(self);
	return self;
}
