mixmonitor_ds_close_fs(struct mixmonitor_ds *mixmonitor_ds)
{
	unsigned char quitting = 0;

	if (mixmonitor_ds->fs) {
		quitting = 1;
		ast_closestream(mixmonitor_ds->fs);
		mixmonitor_ds->fs = NULL;
		ast_verb(2, "MixMonitor close filestream (mixed)\n");
	}

	if (mixmonitor_ds->fs_read) {
		quitting = 1;
		ast_closestream(mixmonitor_ds->fs_read);
		mixmonitor_ds->fs_read = NULL;
		ast_verb(2, "MixMonitor close filestream (read)\n");
	}

	if (mixmonitor_ds->fs_write) {
		quitting = 1;
		ast_closestream(mixmonitor_ds->fs_write);
		mixmonitor_ds->fs_write = NULL;
		ast_verb(2, "MixMonitor close filestream (write)\n");
	}

	if (quitting) {
		mixmonitor_ds->fs_quit = 1;
	}
}
