toggle_test_count (AppData * appdata)
{

	if (appdata->test_count > 0)
	{
		appdata->test_count--;
	}
	else
	{


		add_test_info_time (appdata);
		g_source_remove (appdata->test_idle_id);


		if (appdata->test_only_one)
		{
			appdata->test_type = 99;
		}
		else
		{
			appdata->test_type++;
			appdata->test_count = appdata->test_count_selected;
			appdata->test_state_data = 0;
		}

		perform_test_type (appdata);
	}
}
