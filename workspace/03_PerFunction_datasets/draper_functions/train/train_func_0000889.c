node_set_vendor(gnutella_node_t *n, const char *vendor)
{
	char *wbuf = NULL;
	size_t size = 0;

	if (n->flags & NODE_F_FAKE_NAME) {
		size = w_concat_strings(&wbuf, "!", vendor, (void *) 0);
	} else {
		static const char full[] = "Morpheus";
		bool fix;


		fix = is_strcaseprefix(vendor, "morph") &&
				0 != ascii_strcmp_delimit(vendor, full, " /");
		if (fix)
			size = w_concat_strings(&wbuf, full, " (", vendor, ")", (void *) 0);
	}

	atom_str_change(&n->vendor, lazy_iso8859_1_to_utf8(wbuf ? wbuf : vendor));

	if (wbuf) {
		wfree(wbuf, size);
		wbuf = NULL;
	}

    node_fire_node_info_changed(n);
}
