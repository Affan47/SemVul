do_cmd_wizard(void)
{

	if (!(p_ptr->noscore & NOSCORE_WIZARD))
	{

		msg("You are about to enter 'wizard' mode for the very first time!");
		msg("This is a form of cheating, and your game will not be scored!");
		message_flush();


		if (!get_check("Are you sure you want to enter wizard mode? "))
			return;


		p_ptr->noscore |= NOSCORE_WIZARD;
	}


	if (p_ptr->wizard)
	{
		p_ptr->wizard = FALSE;
		msg("Wizard mode off.");
	}
	else
	{
		p_ptr->wizard = TRUE;
		msg("Wizard mode on.");
	}


	p_ptr->update |= (PU_MONSTERS);


	p_ptr->redraw |= (PR_TITLE);
}
