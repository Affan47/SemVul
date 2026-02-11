success(string message)
{
	++me->copiedCount;
	--me->inProgress;
	reportProgress(0, 0, 0, 0);
	me->doSomething(message);
}
