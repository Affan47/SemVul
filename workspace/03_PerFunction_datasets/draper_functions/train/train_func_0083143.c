multi_can_message(net_player *p)
{
	int max_rank;
	ship *sp;


	if(p->flags & NETINFO_FLAG_OBSERVER){
		return 0;
	}

	switch(Netgame.options.squad_set){

	case MSO_SQUAD_RANK:
		max_rank = multi_get_highest_rank();
		if(p->m_player->stats.rank < max_rank){
			return 0;
		}
		break;


	case MSO_SQUAD_LEADER:

		if(p->m_player->objnum < 0){
			return 0;
		}


		sp = &Ships[Objects[p->m_player->objnum].instance];
		if (sp->ship_name[strlen(sp->ship_name)-1] == '1')
		{
			return 0;
		}
		break;


	case MSO_SQUAD_ANY:
		break;


	case MSO_SQUAD_HOST:
		if(!(p->flags & NETINFO_FLAG_GAME_HOST)){
			return 0;
		}
		break;
	}

	return 1;
}
