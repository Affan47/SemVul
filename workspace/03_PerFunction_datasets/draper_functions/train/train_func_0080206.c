Ucc_done
	(
	int exit_code,
	Exec_box *box,
	gpointer user_data
	)
	{
	if (exit_code == 0)
		{
		ExultStudio::get_instance()->reload_usecode();
		box->add_message("Reloaded usecode\n");
		}
	}
