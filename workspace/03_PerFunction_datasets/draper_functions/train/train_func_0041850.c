IoCoroutine_rawResume(IoCoroutine *self)
{
	if(DATA(self)->cid)
	{
		IoCoroutine *current = IoState_currentCoroutine(IOSTATE);
		IoState_setCurrentCoroutine_(IOSTATE, self);

		Coro_switchTo_(IoCoroutine_rawCoro(current), IoCoroutine_rawCoro(self));


	}
	else
	{

		IoCoroutine_rawRun(self);
	}

	return self;
}
