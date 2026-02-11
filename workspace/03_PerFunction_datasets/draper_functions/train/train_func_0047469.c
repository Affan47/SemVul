DoCheat(struct mame_bitmap * bitmap)
{
	int	i;

	if(input_ui_pressed(IPT_UI_TOGGLE_CHEAT))
	{
		if(ShiftKeyPressed())
		{
			watchesDisabled ^= 1;

			usrintf_showmessage_secs(1, "%s %s", ui_getstring(UI_watchpoints), watchesDisabled ? ui_getstring (UI_off) : ui_getstring (UI_on));
		}
		else
		{
			cheatsDisabled ^= 1;

			usrintf_showmessage_secs(1, "%s %s", ui_getstring(UI_cheats), cheatsDisabled ? ui_getstring (UI_off) : ui_getstring (UI_on));

			if(cheatsDisabled)
			{
				for(i = 0; i < cheatListLength; i++)
				{
					TempDeactivateCheat(&cheatList[i]);
				}
			}
		}
	}

	DisplayWatches(bitmap);

	if(cheatsDisabled)
		return;

	for(i = 0; i < cheatListLength; i++)
	{
		DoCheatEntry(&cheatList[i]);
	}
}
