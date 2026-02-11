IoCoroutine_rawRun(IoCoroutine *self)
{
	Coro *coro = DATA(self)->cid;

	if (!coro)
	{
		coro = Coro_new();
		DATA(self)->cid = coro;
	}

	{
		IoObject *stackSize = IoObject_getSlot_(self, IOSTATE->stackSizeSymbol);

		if(ISNUMBER(stackSize))
		{
			Coro_setStackSize_(coro, CNUMBER(stackSize));
		}
	}

	{
		IoCoroutine *current = IoState_currentCoroutine(IOSTATE);
		Coro *currentCoro = IoCoroutine_rawCoro(current);

		Coro_startCoro_(currentCoro, coro, self, (CoroStartCallback *)IoCoroutine_coroStart);

	}
}
