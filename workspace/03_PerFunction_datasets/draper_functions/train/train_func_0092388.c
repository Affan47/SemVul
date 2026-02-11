is_hostile_nation(short nationRecno)
{
	if(nationRecno==0)
		return 0;

	err_when(nationRecno>7);
	return (hostile_nation_bits & (0x1 << nationRecno));
}
