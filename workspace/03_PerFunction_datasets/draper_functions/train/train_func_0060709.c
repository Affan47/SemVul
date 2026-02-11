file_set_load_from_crc_file(file_set *set, const char* crc_file_path)
{
	FILE *fd;
	int line_num;
	char buf[2048];
	hash_check hc;

	if( !(fd = rsh_fopen_bin(crc_file_path, "rb") )) {

		return (errno == ENOENT ? 0 : -1);
	}
	for(line_num = 0; fgets(buf, 2048, fd); line_num++) {
		char* line = buf;


		if(line_num == 0 && buf[0] == (char)0xEF && buf[1] == (char)0xBB && buf[2] == (char)0xBF) line += 3;

		if(*line == 0) continue;

		if(is_binary_string(line)) {
			log_msg("error: skipping binary file %s\n", crc_file_path);
			fclose(fd);
			return -1;
		}

		if(IS_COMMENT(*line) || *line == '\r' || *line == '\n') continue;


		if(hash_check_parse_line(line, &hc, !feof(fd))) {

			if(hc.file_path) file_set_add_name(set, hc.file_path);
		}
	}
	fclose(fd);
	return 0;
}
