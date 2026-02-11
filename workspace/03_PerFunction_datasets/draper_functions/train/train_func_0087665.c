bell(const char *reason)
{

	Term_fresh();


	if (character_generated && reason)
	{
		message_add(reason, MSG_BELL);


		p_ptr->redraw |= (PR_MESSAGE);
		redraw_stuff(p_ptr);
	}


	flush();
}
