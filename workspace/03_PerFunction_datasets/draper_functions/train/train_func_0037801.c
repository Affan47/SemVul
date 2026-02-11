panic_search(void)
{
        struct foreach_data foreach_data, *fd;
	char *p1, *p2, *tp;
	ulong lasttask, dietask, found;
	char buf[BUFSIZE];
	struct task_context *tc;

	if ((lasttask = get_dumpfile_panic_task())) {
		found = TRUE;
		goto found_panic_task;
	}

        BZERO(&foreach_data, sizeof(struct foreach_data));
        fd = &foreach_data;
	fd->keys = 1;
	fd->keyword_array[0] = FOREACH_BT;
	fd->flags |= (FOREACH_t_FLAG|FOREACH_o_FLAG);

	dietask = lasttask = NO_TASK;

	found = FALSE;

	open_tmpfile();

	foreach(fd);

        rewind(pc->tmpfile);

        while (fgets(buf, BUFSIZE, pc->tmpfile)) {
		if ((p1 = strstr(buf, "  TASK: "))) {
			p1 += strlen("  TASK: ");
			p2 = p1;
			while (!whitespace(*p2))
				p2++;
			*p2 = NULLCHAR;
			lasttask = htol(p1, RETURN_ON_ERROR, NULL);
		}

		if (strstr(buf, " panic at ")) {
			found = TRUE;
			break;
		}

		if (strstr(buf, " crash_kexec at ") ||
		    strstr(buf, " .crash_kexec at ")) {
			found = TRUE;
			break;
		}

                if (strstr(buf, " die at ")) {
			switch (dietask)
			{
			case NO_TASK:
				dietask = lasttask;
				break;
			default:
				if (dietask != lasttask)
					dietask = NO_TASK+1;
				break;
			}
                }
	}

	close_tmpfile();

	if (!found && (dietask > (NO_TASK+1)) && task_has_cpu(dietask, NULL)) {
		lasttask = dietask;
		found = TRUE;
	}

	if (dietask == (NO_TASK+1))
		error(WARNING, "multiple active tasks have called die\n\n");

	if (CRASHDEBUG(1) && found)
		error(INFO, "panic_search: %lx (via foreach bt)\n",
			lasttask);

found_panic_task:
	populate_panic_threads();

	if (found) {
		if ((tc = task_to_context(lasttask)))
			return tc;


                if ((tp = fill_task_struct(lasttask))) {
			if ((tc = store_context(NULL, lasttask, tp))) {
				tt->running_tasks++;
				return tc;
			}
		}
	}

	if (CRASHDEBUG(1))
		error(INFO, "panic_search: failed (via foreach bt)\n");

	return NULL;
}
