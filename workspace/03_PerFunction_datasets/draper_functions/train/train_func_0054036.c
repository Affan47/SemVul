save_game(void)
{

	disturb(1, 0);


	message_flush();


	handle_stuff();


	prt("Saving game...", 0, 0);


	Term_fresh();


	my_strcpy(p_ptr->died_from, "(saved)", sizeof(p_ptr->died_from));


	signals_ignore_tstp();


	if (old_save())
	{
		prt("Saving game... done.", 0, 0);
	}


	else
	{
		prt("Saving game... failed!", 0, 0);
	}


	signals_handle_tstp();


	Term_fresh();


	my_strcpy(p_ptr->died_from, "(alive and well)", sizeof(p_ptr->died_from));
}
