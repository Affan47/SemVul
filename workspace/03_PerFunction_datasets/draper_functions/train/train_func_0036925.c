Key_ClearStates (void)
{
	int		i;

	anykeydown = 0;

	for (i = 0; i < MAX_KEYS; i++)
	{

		if ( keys[i].down )
			Key_Event( i, false, 0 );
		keys[i].down = false;
		keys[i].repeats = 0;
	}
}
