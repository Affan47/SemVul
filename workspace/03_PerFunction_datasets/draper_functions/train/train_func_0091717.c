vm_event_state_init(void)
{
	int i, stringlen, total;
	int c ATTRIBUTE_UNUSED;
	long count, enum_value;
	struct gnu_request *req;
	char *arglist[MAXARGS];
	char buf[BUFSIZE];
	char *start;

	if (vt->flags & VM_EVENT)
		return TRUE;

        if ((vt->nr_vm_event_items == -1) ||
	    !per_cpu_symbol_search("per_cpu__vm_event_states"))
                goto bailout;

	if (!enumerator_value("NR_VM_EVENT_ITEMS", &count))
		return FALSE;

	vt->nr_vm_event_items = count;

        open_tmpfile();
        req = (struct gnu_request *)GETBUF(sizeof(struct gnu_request));
        req->command = GNU_GET_DATATYPE;
        req->name = "vm_event_item";
        req->flags = GNU_PRINT_ENUMERATORS;
        gdb_interface(req);
        FREEBUF(req);

	stringlen = 1;

        rewind(pc->tmpfile);
        while (fgets(buf, BUFSIZE, pc->tmpfile)) {
		if (strstr(buf, "{") || strstr(buf, "}"))
			continue;
		clean_line(buf);
		c = parse_line(buf, arglist);
		if (STREQ(arglist[0], "NR_VM_EVENT_ITEMS"))
			break;
		else
			stringlen += strlen(arglist[0]);
        }

	total = stringlen + vt->nr_vm_event_items +
		(sizeof(void *) * vt->nr_vm_event_items);
        if (!(vt->vm_event_items = (char **)malloc(total))) {
		close_tmpfile();
                error(FATAL, "cannot malloc vm_event_items cache\n");
	}
	BZERO(vt->vm_event_items, total);

	start = (char *)&vt->vm_event_items[vt->nr_vm_event_items];

        rewind(pc->tmpfile);
        while (fgets(buf, BUFSIZE, pc->tmpfile)) {
                if (strstr(buf, "{") || strstr(buf, "}"))
                        continue;
		c = parse_line(buf, arglist);
		if (enumerator_value(arglist[0], &enum_value))
			i = enum_value;
		else {
			close_tmpfile();
			goto bailout;
		}
		if (i < vt->nr_vm_event_items) {
			vt->vm_event_items[i] = start;
			strcpy(start, arglist[0]);
			start += strlen(arglist[0]) + 1;
		}
        }
	close_tmpfile();

	vt->flags |= VM_EVENT;
	return TRUE;

bailout:
	vt->nr_vm_event_items = -1;
	return FALSE;
}
