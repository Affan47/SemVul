set_hostile_nation(int nationRecno)
{
	if(nationRecno==0)
		return;

	err_when(nationRecno>7);
	monster_nation_relation |= (0x1 << nationRecno);
}
