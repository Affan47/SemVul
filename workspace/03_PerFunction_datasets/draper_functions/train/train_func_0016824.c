request_trade_embargo()
{


	if( reply_type == REPLY_WAITING || !should_disp_reply )
	{
		if( viewing_nation_recno == from_nation_recno )
		{
			str  = "You request ";
			str += to_nation_name();
		}
		else
		{
			str  = from_nation_name();
			str += " requests you";
		}

		str += " to join an embargo on trade with ";
		str += nation_array[talk_para1]->nation_name();
		str += nation_color_code_str(talk_para1);
		str += ".";
	}
	else
	{
		if( viewing_nation_recno == from_nation_recno )
		{
			str = to_nation_name();

			if( reply_type == REPLY_ACCEPT )
				str += " agrees";
			else
				str += " refuses";

			str += " to join an embargo on trade with ";
			str += nation_array[talk_para1]->nation_name();
			str += nation_color_code_str(talk_para1);
			str += ".";
		}
		else
		{
			if( reply_type == REPLY_ACCEPT )
				str = "You agree";
			else
				str = "You refuse";

			str += " to join an embargo on trade with ";
			str += nation_array[talk_para1]->nation_name();
			str += nation_color_code_str(talk_para1);
			str += " as requested by ";
			str += from_nation_name();
			str += ".";
		}
	}
}
