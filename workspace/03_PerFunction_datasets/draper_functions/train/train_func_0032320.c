check_space_left(int lfd, struct auditd_consumer_data *data)
{
	int rc;
	struct statfs buf;
	struct daemon_conf *config = data->config;

        rc = fstatfs(lfd, &buf);
        if (rc == 0) {
		if (buf.f_bavail < 5) {

			fs_space_left = 0;
			do_disk_full_action(data);
		} else {
			unsigned long blocks;
			unsigned long block_size = buf.f_bsize;
		        blocks = config->space_left * (MEGABYTE/block_size);
        		if (buf.f_bavail < blocks) {
				if (fs_space_warning == 0) {
					do_space_left_action(data, 0);
					fs_space_warning = 1;
				}
			} else if (fs_space_warning &&
					config->space_left_action == FA_SYSLOG){

				fs_space_warning = 0;
			}
		        blocks=config->admin_space_left * (MEGABYTE/block_size);
        		if (buf.f_bavail < blocks) {
				if (fs_admin_space_warning == 0) {
					do_space_left_action(data, 1);
					fs_admin_space_warning = 1;
				}
			} else if (fs_admin_space_warning &&
				config->admin_space_left_action == FA_SYSLOG) {

				fs_admin_space_warning = 0;
			}
		}
	}
	else audit_msg(LOG_DEBUG, "fstatfs returned:%d, %s", rc,
			strerror(errno));
}
