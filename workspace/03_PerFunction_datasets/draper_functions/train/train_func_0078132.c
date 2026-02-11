rw_rewrite_msg_finish(struct rwmsginfo *rwinfo)
{
int	j=0;

	while (rwinfo->inheaders)
	{
		if (rw_rewrite_msgheaders("\n", 1, rwinfo))
		{
			j= -1;
			break;
		}
	}

	if (rwinfo->headerbuf)
		free(rwinfo->headerbuf);
	return (j);
}
