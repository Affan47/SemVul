print_sfv_file_header(void)
{

	if(opt.fmt == FMT_SFV && opt.mode == 0) {
		char **f;
		print_sfv_banner(rhash_data.out);

		for(f = opt.files; *f != NULL; f++) {
			if(opt.flags & OPT_RECURSIVE) {
				struct rsh_stat_struct stat_buf;
				if(rsh_stat(*f, &stat_buf) < 0) {
					continue;
				}

				if(S_ISDIR(stat_buf.st_mode)) {
					find_file(*f, find_file_callback, 0, opt.find_max_depth, (void*)1);
					continue;
				}
			}
			print_sfv_header_line(rhash_data.out, *f, *f);
		}
		fflush(rhash_data.out);
	}
}
