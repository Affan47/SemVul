WI_fragSum(int playernum)
{
    int		i;
    int		frags = 0;

    for (i=0 ; i<MAXPLAYERS ; i++)
    {
	if (playeringame[i]
	    && i!=playernum)
	{
	    frags += plrs[playernum].frags[i];
	}
    }


    frags -= plrs[playernum].frags[playernum];


    return frags;
}
