set_wingnum(int objnum, int wingnum)
{
	int	shipnum, ai_index;

	Assert(Objects[objnum].type == OBJ_SHIP);

	shipnum = Objects[objnum].instance;

	Assert((shipnum >= 0) && (shipnum < MAX_SHIPS));

	ai_index = Ships[shipnum].ai_index;

	Assert( (ai_index >= 0) && (ai_index < MAX_AI_INFO) );

	Ai_info[ai_index].wing = wingnum;
}
