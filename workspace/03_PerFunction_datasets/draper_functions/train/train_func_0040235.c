get_decoded_outfilename(const char *infilename)
{
	const char *suffix;
	if(option_values.analyze) {
		suffix = ".ana";
	}
	else if(option_values.force_raw_format) {
		suffix = ".raw";
	}
	else if(option_values.force_aiff_format) {
		suffix = ".aiff";
	}
	else if(option_values.force_rf64_format) {
		suffix = ".rf64";
	}
	else if(option_values.force_wave64_format) {
		suffix = ".w64";
	}
	else {
		suffix = ".wav";
	}
	return get_outfilename(infilename, suffix);
}
