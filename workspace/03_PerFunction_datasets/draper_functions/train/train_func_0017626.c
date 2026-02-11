strace_read_llseek(char * line, list_t * list) {
	llseek_item_t * op_item;
	char flags[MAX_STRING];
	int retval;
   char start_time[MAX_TIME_STRING];
   char dur[MAX_TIME_STRING];

	op_item = new_llseek_item();

	op_item->type = OP_LLSEEK;

	if ((retval = sscanf(line, " %d %s %*[^(](%d, %"SCNi64", \[%"SCNi64"], %[^)]) = %"SCNi64"%*[^<]<%[^>]", &op_item->o.info.pid, start_time, &op_item->o.fd, &op_item->o.offset, &op_item->o.f_offset,
					flags, &op_item->o.retval, dur)) == EOF) {
		ERRORPRINTF("Error: unexpected end of file%s", "\n");
		free(op_item);
		return -1;
	}

	if (retval != 8) {
		ERRORPRINTF("Error: It was not able to match all fields required.%s", "\n");
		ERRORPRINTF("Failing line: %s", line);
		free(op_item);
		return -1;
	}

	op_item->o.flag = read_seek_flag(flags);

   op_item->o.info.start = read_time(start_time);
   op_item->o.info.dur = read_duration(dur);

	list_append(list, &op_item->item);
	return 0;
}
