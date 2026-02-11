can_accept()
{
	Nation* toNation = nation_array[to_nation_recno];

	switch( talk_id )
	{
		case TALK_REQUEST_BUY_FOOD:
			return toNation->food >= talk_para1;

		case TALK_DEMAND_TRIBUTE:
		case TALK_DEMAND_AID:
			return toNation->cash >= talk_para1;

		case TALK_DEMAND_TECH:
			return tech_res[talk_para1]->get_nation_tech_level(to_nation_recno) > 0;
	}

	return 1;
}
