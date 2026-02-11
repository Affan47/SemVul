totem_options_process_late (Totem *totem, const TotemCmdLineOptions *options)
{
	if (options->togglecontrols)
		totem_action_toggle_controls (totem);


	totem->index = options->playlistidx;


	totem->seek_to_start = options->seek;
}
