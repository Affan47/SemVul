get_common_commits(void)
{
	static char line[1000];
	unsigned char sha1[20];
	char last_hex[41];

	save_commit_buffer = 0;

	for (;;) {
		int len = packet_read_line(0, line, sizeof(line));
		reset_timeout();

		if (!len) {
			if (have_obj.nr == 0 || multi_ack)
				packet_write(1, "NAK\n");
			if (stateless_rpc)
				exit(0);
			continue;
		}
		strip(line, len);
		if (!prefixcmp(line, "have ")) {
			switch (got_sha1(line+5, sha1)) {
			case -1:
				if (multi_ack && ok_to_give_up()) {
					const char *hex = sha1_to_hex(sha1);
					if (multi_ack == 2)
						packet_write(1, "ACK %s ready\n", hex);
					else
						packet_write(1, "ACK %s continue\n", hex);
				}
				break;
			default:
				memcpy(last_hex, sha1_to_hex(sha1), 41);
				if (multi_ack == 2)
					packet_write(1, "ACK %s common\n", last_hex);
				else if (multi_ack)
					packet_write(1, "ACK %s continue\n", last_hex);
				else if (have_obj.nr == 1)
					packet_write(1, "ACK %s\n", last_hex);
				break;
			}
			continue;
		}
		if (!strcmp(line, "done")) {
			if (have_obj.nr > 0) {
				if (multi_ack)
					packet_write(1, "ACK %s\n", last_hex);
				return 0;
			}
			packet_write(1, "NAK\n");
			return -1;
		}
		die("git upload-pack: expected SHA1 list, got '%s'", line);
	}
}
