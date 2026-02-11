SendCopyEnd(CopyState cstate)
{
	if (cstate->copy_dest == COPY_NEW_FE)
	{

		Assert(cstate->fe_msgbuf->len == 0);

		pq_putemptymessage('c');
	}
	else
	{
		CopySendData(cstate, "\\.", 2);

		CopySendEndOfRow(cstate);
		pq_endcopyout(false);
	}
}
