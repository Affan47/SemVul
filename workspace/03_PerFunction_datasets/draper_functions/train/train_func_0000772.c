bogons_load(FILE *f)
{
	char line[1024];
	uint32 ip, netmask;
	int linenum = 0;
	int bits;
	iprange_err_t error;
	filestat_t buf;

	bogons_db = iprange_new();
	if (-1 == fstat(fileno(f), &buf)) {
		g_warning("cannot stat %s: %m", bogons_file);
	} else {
		bogons_mtime = buf.st_mtime;
	}

	while (fgets(line, sizeof line, f)) {
		linenum++;


		if (!file_line_chomp_tail(line, sizeof line, NULL)) {
			g_warning("%s, line %d: too long a line", bogons_file, linenum);
			break;
		}

		if (file_line_is_skipable(line))
			continue;

		if (!string_to_ip_and_mask(line, &ip, &netmask)) {
			g_warning("%s, line %d: invalid IP or netmask \"%s\"",
				bogons_file, linenum, line);
			continue;
		}

		bits = netmask_to_cidr(netmask);
		error = iprange_add_cidr(bogons_db, ip, bits, 1);

		switch (error) {
		case IPR_ERR_OK:
			break;

		default:
			g_warning("%s, line %d: rejected entry \"%s\" (%s/%d): %s",
				bogons_file, linenum, line, ip_to_string(ip), bits,
				iprange_strerror(error));
			continue;
		}
	}

	iprange_sync(bogons_db);

	if (GNET_PROPERTY(reload_debug)) {
		g_debug("loaded %u bogus IP ranges (%u hosts)",
			iprange_get_item_count(bogons_db),
			iprange_get_host_count4(bogons_db));
	}

	return iprange_get_item_count(bogons_db);
}
