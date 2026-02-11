read_config_file(const string &input_filename, const string &root)
{
	string fname;

	CTRACE("Configuration::read_config_file");

	fname=input_filename;


	if((fname.find("./")!=0) && (fname[0]!='/'))
	{
#if ((defined XWIN) || (defined BEOS) || (defined MACOSX))
		const char *f1=getenv("HOME");
		if(f1)
		{

			fname=f1;
#if defined(BEOS)
			fname+="/config/settings/";
#elif defined(MACOSX)
			fname+="/Library/Preferences/";
#else
			fname+="/.";
#endif
			fname+=input_filename;
		}
		else
			fname=input_filename;
#else


		fname=input_filename;
#endif
	}

	return read_abs_config_file(fname, root);
}
