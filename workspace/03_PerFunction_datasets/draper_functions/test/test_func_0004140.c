strace_read_open(char * line, list_t * list) {
	open_item_t * op_item;
	char flags[MAX_STRING];
	int retval;
   char start_time[MAX_TIME_STRING];
   char dur[MAX_TIME_STRING] = "0";

	op_item = new_open_item();
	op_item->type = OP_OPEN;
	if ((retval = sscanf(line, "%d %s %*[^\"]\"%" QUOTE(MAX_STRING) "[^\"]\", %[^,], %u) = %d%*[^<]<%[^>]", &op_item->o.info.pid, start_time, op_item->o.name, flags, &op_item->o.mode,
					&op_item->o.retval, dur)) == EOF) {

		ERRORPRINTF("Error: unexpected end of file%s", "\n");
		free(op_item);
		return -1;
	}

	if (retval != 7) {
		if ((retval = sscanf(line, "%d %s %*[^\"]\"%" QUOTE(MAX_STRING) "[^\"]\", %[^)]) = %d%*[^<]<%[^>]", &op_item->o.info.pid, start_time, op_item->o.name, flags,
						&op_item->o.retval, dur)) == EOF) {
			ERRORPRINTF("Error: unexpected end of file%s", "\n");
			free(op_item);
			return -1;
		}

		if ( retval != 6) {
			ERRORPRINTF("Error: It was not able to match all fields required: %d\n", retval);
			ERRORPRINTF("Failing line: %s", line);
			free(op_item);
			return -1;
		}
		op_item->o.mode = MODE_UNDEF;
	}

	op_item->o.flags = read_open_flags(flags);

   op_item->o.info.start = read_time(start_time);
   op_item->o.info.dur = read_duration(dur);

	list_append(list, &op_item->item);
	return 0;
}
