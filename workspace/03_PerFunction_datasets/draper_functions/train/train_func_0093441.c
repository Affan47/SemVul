calculate_and_print_sums(FILE* out, file_t* file, const char *print_path)
{
	struct file_info info;
	timedelta_t timer;
	int res = 0;

	memset(&info, 0, sizeof(info));
	info.file = file;
	info.full_path = rsh_strdup(file->path);
	file_info_set_print_path(&info, print_path);
	info.size = 0;

	info.sums_flags = opt.sum_flags;

	if (file->mode & FILE_IFSTDIN) {
		print_path = "(stdin)";
	} else {
		if (file->mode & FILE_IFDIR) return 0;
		info.size = file->size;
	}


	init_percents(&info);
	rsh_timer_start(&timer);

	if (info.sums_flags) {

		if (calc_sums(&info) < 0) {

			log_file_error(file->path);
			res = -1;
		}
		if (rhash_data.interrupted) {
			report_interrupted();
			return 0;
		}
	}

	info.time = rsh_timer_stop(&timer);
	finish_percents(&info, res);

	if (opt.flags & OPT_EMBED_CRC) {

		rename_file_by_embeding_crc32(&info);
	}

	if ((opt.mode & MODE_TORRENT) && !opt.bt_batch_file) {
		save_torrent(&info);
	}

	if ((opt.mode & MODE_UPDATE) && opt.fmt == FMT_SFV) {

		print_sfv_header_line(rhash_data.upd_fd, file, 0);
		if (opt.flags & OPT_VERBOSE) {
			print_sfv_header_line(rhash_data.log, file, 0);
			fflush(rhash_data.log);
		}
		file_cleanup(file);
	}

	if (rhash_data.print_list && res >= 0) {
		if (!opt.bt_batch_file) {
			print_line(out, rhash_data.print_list, &info);
			fflush(out);


			if ((opt.mode & MODE_UPDATE) && (opt.flags & OPT_VERBOSE)) {
				print_line(rhash_data.log, rhash_data.print_list, &info);
				fflush(rhash_data.log);
			}
		}

		if ((opt.flags & OPT_SPEED) && info.sums_flags) {
			print_file_time_stats(&info);
		}
	}
	free(info.full_path);
	file_info_destroy(&info);
	return res;
}
