RulesChangeFunc ( void *self )
{

	if (s_rules_box.curvalue == 0)
	{
		s_maxclients_field.generic.statusbar = NULL;
		s_startserver_dmoptions_action.generic.statusbar = NULL;
	}
	else if(s_rules_box.curvalue == 1)
	{
		s_maxclients_field.generic.statusbar = "4 maximum for cooperative";
		if (atoi(s_maxclients_field.buffer) > 4)
			strcpy( s_maxclients_field.buffer, "4" );
		s_startserver_dmoptions_action.generic.statusbar = "N/A for cooperative";
	}


	else if(Developer_searchpath() == 2)
	{
		if (s_rules_box.curvalue == 2)
		{
			s_maxclients_field.generic.statusbar = NULL;
			s_startserver_dmoptions_action.generic.statusbar = NULL;
		}
	}


}
