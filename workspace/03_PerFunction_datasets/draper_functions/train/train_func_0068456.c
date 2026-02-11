imonlcd_close(Driver *drvthis)
{
	PrivateData *p = drvthis->private_data;
	time_t tt;
	struct tm *t;
	uint64_t data;

	if (p != NULL) {
		if (p->imon_fd >= 0) {
			if (p->on_exit == ON_EXIT_SHOWMSG) {


				report(RPT_INFO, "%s: closing, leaving \"goodbye\" message.", drvthis->name);
			} else if (p->on_exit == ON_EXIT_BLANKSCREEN) {


				report(RPT_INFO, "%s: closing, turning backlight off.", drvthis->name);
				send_command_data(p->command_shutdown, p);
				send_command_data(p->command_clear_alarm, p);
			} else {


				report(RPT_INFO, "%s: closing, showing clock.", drvthis->name);

				tt = time(NULL);
				t = localtime(&tt);

				data = p->command_display;
				data += ((uint64_t) t->tm_sec << 48);
				data += ((uint64_t) t->tm_min << 40);
				data += ((uint64_t) t->tm_hour << 32);
				data += ((uint64_t) t->tm_mday << 24);
				data += ((uint64_t) t->tm_mon << 16);
				data += (((uint64_t) t->tm_year) << 8);
				data += 0x80;
				send_command_data(data, p);
				send_command_data(p->command_clear_alarm, p);
			}

			close(p->imon_fd);
		}
		if (p->framebuf != NULL)
			free(p->framebuf);
		p->framebuf = NULL;

		free(p);
	}
	drvthis->store_private_ptr(drvthis, NULL);
}
