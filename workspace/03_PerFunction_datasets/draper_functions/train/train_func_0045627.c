put_spy_rec(int recNo, int x, int y, int refreshFlag)
{
	int  spyRecno = spy_filter(recNo);
	Spy* spyPtr   = spy_array[spyRecno];

	x+=3;
	y+=5;


	int 	 cloakedRankId  = spyPtr->cloaked_rank_id();
	int 	 cloakedSkillId = spyPtr->cloaked_skill_id();
	String str;

	switch( cloakedRankId )
	{
		case RANK_KING:
			str = "U_KING";
			break;

		case RANK_GENERAL:
			str = "U_GENE";
			break;

		case RANK_SOLDIER:
			if( cloakedSkillId )
			{
				str  = "U_";
				str += Skill::skill_code_array[cloakedSkillId-1];
			}
			else
			{
				str = "";
			}
			break;
	}

	if( str.len() > 0 )
		image_icon.put_back(x, y+1, str);


	vga_back.put_bitmap( x+13, y-4, race_res[spyPtr->race_id]->icon_bitmap_ptr );


	font_san.put( x+39, y, race_res[spyPtr->race_id]->get_name(spyPtr->name_id), 0, 185 );


	int tx = x+170;

	if( spyPtr->cloaked_nation_recno==0 )
	{
		vga_back.bar( tx, y, tx+12, y+12, V_WHITE );
		vga_back.rect( tx, y, tx+12, y+12, 1, VGA_GRAY+8 );
	}
	else
	{
		nation_array[spyPtr->cloaked_nation_recno]->disp_nation_color(tx, y+2);
	}


	switch( spyPtr->spy_place )
	{
		case SPY_FIRM:
			str = firm_res[firm_array[spyPtr->spy_place_para]->firm_id]->name;
			break;

		case SPY_TOWN:
			str = town_array[spyPtr->spy_place_para]->town_name();
			break;

		case SPY_MOBILE:
		{
			Unit* unitPtr = unit_array[spyPtr->spy_place_para];

			switch( unitPtr->unit_mode )
			{
				case UNIT_MODE_CONSTRUCT:
					str = firm_res[firm_array[unitPtr->unit_mode_para]->firm_id]->name;
					break;

				case UNIT_MODE_ON_SHIP:
					str = "On Ship";
					break;

				default:
					str = "Mobile";
			}
			break;
		}

		default:
			str = "";
	}

	font_san.put( x+205, y, str );

	font_san.put( x+335, y, spyPtr->spy_skill );
	font_san.put( x+385, y, spyPtr->spy_loyalty );
	font_san.put( x+435, y, spyPtr->action_str() );
}
