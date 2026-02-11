rename_file_to_embed_crc32(struct file_info *info)
{
	size_t len = strlen(info->full_path);
	const char* p = info->full_path + len;
	const char* c = p - 1;
	char* new_path;
	char* insertion_point;
	unsigned crc32_be;
	assert((info->rctx->hash_id & RHASH_CRC32) != 0);


	if(find_embedded_crc32(info->print_path, &crc32_be)) {

		if(be2me_32(crc32_be) !=
			*(unsigned*)rhash_get_context_ptr(info->rctx, RHASH_CRC32)) {
			char crc32_str[9];
			rhash_print(crc32_str, info->rctx, RHASH_CRC32, RHPR_UPPERCASE);
			log_msg("warning: wrong embedded sum, should be %s\n", crc32_str);
		} else return 0;
	}


	for(; c >= info->full_path && !IS_PATH_SEPARATOR(*c); c--) {
		if(*c == '.') {
			p = c;
			break;
		}
	}


	new_path = (char*)rsh_malloc(len + 11);
	insertion_point = new_path + (p - info->full_path);
	memcpy(new_path, info->full_path, p - info->full_path);
	if(opt.embed_crc_delimiter && *opt.embed_crc_delimiter) *(insertion_point++) = *opt.embed_crc_delimiter;
	rhash_print(insertion_point+1, info->rctx, RHASH_CRC32, RHPR_UPPERCASE);
	insertion_point[0] = '[';
	insertion_point[9] = ']';
	strcpy(insertion_point + 10, p);


	if(rename(info->full_path, new_path) < 0) {
		fprintf(rhash_data.log, PROGRAM_NAME ": can't move %s to %s: %s\n", info->full_path, new_path, strerror(errno));
		free(new_path);
		return -1;
	}


	if(info->print_path >= info->full_path && info->print_path < p) {
		file_info_set_print_path(info, new_path + len - strlen(info->print_path));
	} else {
		file_info_set_print_path(info, new_path);
	}

	free(info->full_path);
	info->full_path = new_path;
	return 0;
}
