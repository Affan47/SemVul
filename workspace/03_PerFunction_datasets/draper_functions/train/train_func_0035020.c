map_getmaptype(int m)
{
	int type = 0;

	if(m < 0)
		return 0;

	if(map[m].flag.pvp_nightmaredrop)
		type = 5;
	else if(map[m].flag.pvp && map[m].flag.pvp_nocalcrank)
		type = 12;
	else if(map[m].flag.pvp)
		type = 6;
	else if(map[m].flag.gvg)
		type = 8;


	else if(map[m].flag.gvg_noparty)
		type = 9;
	else if(map[m].flag.noskill)
		type = 13;
	else if(map[m].memorial_id)
		type = 20;
	else if(map[m].flag.noteleport)
		type = 10;
	else if(map[m].flag.town)
		type = 0;
	else if(!map[m].flag.nomemo)
		type = 2;
	else
		type = 3;

	return type;
}
