do_major_operation(const CommandLineOptions *options)
{
	unsigned i;
	FLAC__bool ok = true;


	for(i = 0; i < options->num_files; i++)
		ok &= do_major_operation_on_file(options->filenames[i], options);

	return ok;
}
