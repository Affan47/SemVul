pt_identify(struct pt_unit *tape)
{
	int dt, s;
	char *ms[2] = { "master", "slave" };
	char mf[10], id[18];
	char id_cmd[12] = { ATAPI_IDENTIFY, 0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0 };
	char ms_cmd[12] =
	    { ATAPI_MODE_SENSE, 0, 0x2a, 0, 36, 0, 0, 0, 0, 0, 0, 0 };
	char ls_cmd[12] =
	    { ATAPI_LOG_SENSE, 0, 0x71, 0, 0, 0, 0, 0, 36, 0, 0, 0 };
	char buf[36];

	s = pt_atapi(tape, id_cmd, 36, buf, "identify");
	if (s)
		return -1;

	dt = buf[0] & 0x1f;
	if (dt != 1) {
		if (verbose)
			printk("%s: Drive %d, unsupported type %d\n",
			       tape->name, tape->drive, dt);
		return -1;
	}

	xs(buf, mf, 8, 8);
	xs(buf, id, 16, 16);

	tape->flags = 0;
	tape->capacity = 0;
	tape->bs = 0;

	if (!pt_ready_wait(tape, PT_READY_TMO))
		tape->flags |= PT_MEDIA;

	if (!pt_atapi(tape, ms_cmd, 36, buf, "mode sense")) {
		if (!(buf[2] & 0x80))
			tape->flags |= PT_WRITE_OK;
		tape->bs = xn(buf, 10, 2);
	}

	if (!pt_atapi(tape, ls_cmd, 36, buf, "log sense"))
		tape->capacity = xn(buf, 24, 4);

	printk("%s: %s %s, %s", tape->name, mf, id, ms[tape->drive]);
	if (!(tape->flags & PT_MEDIA))
		printk(", no media\n");
	else {
		if (!(tape->flags & PT_WRITE_OK))
			printk(", RO");
		printk(", blocksize %d, %d MB\n", tape->bs, tape->capacity / 1024);
	}

	return 0;
}
