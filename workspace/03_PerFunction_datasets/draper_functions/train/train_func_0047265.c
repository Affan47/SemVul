setup_output(void)
{
	rhash_data.out = stdout;
	rhash_data.log = stderr;

	setup_log_stream(&rhash_data.log, opt.log);
	setup_log_stream(&rhash_data.out, opt.output);

	if(opt.flags & OPT_PERCENTS) {


		if(rhash_data.log == stderr && isatty(2)) {

			percents_output  = &p_perc;
		} else {

			percents_output  = &dots_perc;
		}
	} else {
		percents_output  = &dummy_perc;
	}
}
