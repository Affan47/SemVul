delete_message(char *name)
{
	vboxd_put_message("delete %s", name);

	if (vboxd_get_message())
	{
		if (vboxd_test_response(VBOXD_VAL_DELETEOK)) returnok();

		message("\r\n", "Can't delete; invalid server response! %s", "[RETURN]");
	}
	else message("\r\n", "Can't delete; no server response! %s", "[RETURN]");

	returnerror();
}
