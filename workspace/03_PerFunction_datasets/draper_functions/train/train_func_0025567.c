statuscontrol(int nr)
{
	char *resp;
	char *todo;
	char *answer;
	int   status;

	status = statusleds[nr].status;

	message("", "%s '%s'...", (status ? "Removing" : "Creating"), statusleds[nr].name);

	if (status)
	{
		todo = "removectrl";
		resp = VBOXD_VAL_REMOVECTRLOK;
	}
	else
	{
		todo = "createctrl";
		resp = VBOXD_VAL_CREATECTRLOK;
	}

	vboxd_put_message("%s %s", todo, statusleds[nr].name);

	if ((answer = vboxd_get_message()))
	{
		if (vboxd_test_response(resp))
		{
			if (answer[4] != '1') message("\r\n", "Can't %s '%s'! [RETURN]", (status ? "remove" : "create"), statusleds[nr].name);

			draw_ctrl_status();
		}
	}

	draw_bottom_bar();
}
