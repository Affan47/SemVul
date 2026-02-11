dmesh_parse_addr_port_list(const struct sha1 *sha1, const char *value,
	dmesh_add_cb func, void *udata)
{
	const char *tls_hex, *p, *next;

	tls_hex = NULL;
	next = value;

	while (NULL != (p = next)) {
		const char *start, *endptr;
		host_addr_t addr;
		uint16 port;
		bool ok;

		start = skip_ascii_blanks(p);
		if ('\0' == *start)
			break;

		next = strpbrk(start, ",;");
		if (next) {
			next++;
		}


		if (NULL == tls_hex && (tls_hex = is_strcaseprefix(start, "tls=")))
			continue;


		ok = string_to_host_addr(start, &endptr, &addr);
		if (ok && ':' == *endptr) {
			int error;

			port = parse_uint16(&endptr[1], &endptr, 10, &error);
			ok = !error && port > 0;
		} else {
			port = GTA_PORT;
		}

		if (ok) {
			(*func)(sha1, addr, port, udata);
		} else if (GNET_PROPERTY(dmesh_debug)) {
			g_warning("ignoring invalid compact alt-loc \"%s\"", start);
		}
	}
}
