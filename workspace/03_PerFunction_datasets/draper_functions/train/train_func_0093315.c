migrate()
{


	if( short_para4 == 1 )
		str = "A";
	else
		str = misc.format(short_para4);

	str += " ";
	str += race_res[short_para3]->name;
	str += " ";

	if( short_para5 )
		str += firm_res[short_para5]->worker_title;
	else
		str += "Peasant";

	if( short_para4 == 1 )
		str += " has";
	else
		str += "s have";


	if( nation_array.player_recno && nation_name_id1 == (~nation_array)->nation_name_id )
	{
		str += " emigrated from your village of ";
		str += town_res.get_name(short_para1);
		str += " to ";
		str += town_res.get_name(short_para2);

		if( nation_name_id2 )
		{
			str += " in ";
			str += nation_name2();
		}

		str += ".";
	}
	else
	{
		str += " immigrated from ";
		str += town_res.get_name(short_para1);

		if( nation_name_id1 )
		{
			str += " in ";
			str += nation_name1();
		}

		str += " to your village of ";
		str += town_res.get_name(short_para2);
		str += ".";
	}
}
