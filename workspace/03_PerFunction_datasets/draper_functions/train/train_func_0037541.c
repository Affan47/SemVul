free_yank(n)
    long	n;
{
    if (y_current->y_array != NULL)
    {
	long	    i;

	for (i = n; --i >= 0; )
	{
#ifdef AMIGA
	    if ((i & 1023) == 1023)
	    {


		++no_wait_return;
		smsg((char_u *)_("freeing %ld lines"), i + 1);
		--no_wait_return;
		msg_didout = FALSE;
		msg_col = 0;
	    }
#endif
	    vim_free(y_current->y_array[i]);
	}
	vim_free(y_current->y_array);
	y_current->y_array = NULL;
#ifdef AMIGA
	if (n >= 1000)
	    MSG("");
#endif
    }
}
