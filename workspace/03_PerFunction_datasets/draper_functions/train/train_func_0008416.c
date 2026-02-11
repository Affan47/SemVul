find_file_callback(const char* filepath, int type, void* data)
{
	int res = 0;
	if( !(type & FIND_IFDIR) ) {
		if(data) {
			if(!file_mask_match(opt.files_accept, filepath)) return 0;
			if(filepath[0] == '.' && IS_PATH_SEPARATOR(filepath[1])) filepath += 2;
			print_sfv_header_line(rhash_data.out, filepath, filepath);
		} else {

			file_mask_array* masks = (opt.mode & (MODE_CHECK | MODE_UPDATE) ?
				opt.crc_accept : opt.files_accept);
			if(!file_mask_match(masks, filepath)) return 0;

			if(opt.mode & (MODE_CHECK | MODE_CHECK_EMBEDDED)) {
				res = check_hash_file(filepath, 1);
			} else {
				if(opt.mode & MODE_UPDATE) {
					res = update_hash_file(filepath);
				} else {

					if(filepath[0] == '.' && IS_PATH_SEPARATOR(filepath[1])) filepath += 2;
					res = calculate_and_print_sums(rhash_data.out, filepath, filepath, NULL);
					rhash_data.processed++;
				}
			}
		}
	}
	if(res < 0) rhash_data.error_flag = 1;
	return 1;
}
