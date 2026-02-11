TownDevelopment()
{
	int basedev = BaseDev();
	int df = development - basedev;
	if(df < 0) df = 0;
	if(df > 100) df = 100;

	return df;
}
