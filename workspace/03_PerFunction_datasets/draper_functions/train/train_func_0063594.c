on_test_dialog_ok_button_clicked (gpointer data)
{
	int i;
	if (g_pReciteWord->firstrecite_test->dialog.testagain_group_robutton.
	    selected)
		i = 0;
	else
		i = 1;
	g_pReciteWord->firstrecite_test->dialog.close ();
	if (g_pReciteWord->firstrecite_test->status == FRTS_FIRSTTIMEOVER)
	{
		if (i == 1)
		{


		}
		else
		{
			on_test_start_clicked ();
		}
	}
	else
	{
		if (i==1)
		{
		}
		else
		{
			g_pReciteWord->firstrecite_test->close ();
			g_pReciteWord->ShowFirstRecite_group ();
		}
	}
}
