death_file(void *unused, const char *title)
{
	char buf[1024];
	char ftmp[80];

	(void)unused;
	(void)title;

	strnfmt(ftmp, sizeof(ftmp), "%s.txt", op_ptr->base_name);

	if (get_file(ftmp, buf, sizeof buf))
	{
		errr err;


		screen_save();
		err = file_character(buf, FALSE);
		screen_load();


		if (err)
			msg_print("Character dump failed!");
		else
			msg_print("Character dump successful.");


		message_flush();
	}
}
