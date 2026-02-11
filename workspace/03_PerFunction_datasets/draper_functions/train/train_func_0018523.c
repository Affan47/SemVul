remote_get(const char *name)
{
	struct remote *ret;

	read_config();
	if (!name)
		name = default_remote_name;
	ret = make_remote(name, 0);
	if (name[0] != '/') {
		if (!ret->uri)
			read_remotes_file(ret);
		if (!ret->uri)
			read_branches_file(ret);
	}
	if (!ret->uri)
		add_uri(ret, name);
	if (!ret->uri)
		return NULL;
	ret->fetch = parse_ref_spec(ret->fetch_refspec_nr, ret->fetch_refspec);
	ret->push = parse_ref_spec(ret->push_refspec_nr, ret->push_refspec);
	return ret;
}
