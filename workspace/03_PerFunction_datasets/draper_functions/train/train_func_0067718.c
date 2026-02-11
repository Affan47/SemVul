run_machine_core(void)
{

	artwork_enable(0);


	if (settingsloaded || options.skip_disclaimer || showcopyright(artwork_get_ui_bitmap()) == 0)
	{

		if (showgamewarnings(artwork_get_ui_bitmap()) == 0)
		{

			if (options.skip_gameinfo || showgameinfo(artwork_get_ui_bitmap()) == 0)
			{
				init_user_interface();


				artwork_enable(1);


				if (!gamedrv->rom)
					options.cheat = 0;


				if (options.cheat)
					InitCheat();


				if (Machine->drv->nvram_handler)
				{
					mame_file *nvram_file = mame_fopen(Machine->gamedrv->name, 0, FILETYPE_NVRAM, 0);
					(*Machine->drv->nvram_handler)(nvram_file, 0);
					if (nvram_file)
						mame_fclose(nvram_file);
				}


				cpu_run();
			}
		}
	}
}
