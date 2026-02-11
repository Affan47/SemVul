gottlieb_knocker(void)
{
	if (Machine->samples)
	{
		if (!strcmp(Machine->gamedrv->name,"reactor"))
		{
		}
		else
			sample_start(0,44,0);
	}
}
