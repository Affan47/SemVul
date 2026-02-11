rcancelrequested(void)
{
	return InterruptPending && (QueryCancelPending || ProcDiePending);
}
