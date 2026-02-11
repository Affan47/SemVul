reinit_gdbus (gpointer user_data)
{
	if (!enabled || init_gdbus ())
		return FALSE;


	return TRUE;
}
