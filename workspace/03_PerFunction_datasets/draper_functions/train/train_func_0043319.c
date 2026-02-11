new_postscript_fileCmd()
{
	if (_nword < 4) {
		err("`new postscript file' needs a filename.");
		demonstrate_command_usage();
		return false;
	} else if (_nword > 4) {
		err("`new postscript file' takes just 1 argument, a filename");
		demonstrate_command_usage();
		return false;
	}

	gr_end("!");
	std::string unquoted(_word[3]);
	un_double_quote(unquoted);
	gr_setup_ps_filename(unquoted.c_str());
#if 0

	insert_creator_name_in_PS(argc, argv, psname);
#endif
	gr_begin(2);

	gr_fontID present_font = gr_currentfont();
	gr_setfont(gr_font_Courier);
	gr_setfont(present_font);
	return true;
}
