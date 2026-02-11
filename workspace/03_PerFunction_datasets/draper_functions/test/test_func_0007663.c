parse_conf_rad_attr(const char *opt, int *val)
{
	struct rad_dict_attr_t *attr;

	opt = conf_get_opt("ipoe", opt);

	*val = 0;

	if (opt) {
		if (atoi(opt) > 0)
			*val = atoi(opt);
		else {
			attr = rad_dict_find_attr(opt);
			if (attr)
				*val = attr->id;
			else
				log_emerg("ipoe: couldn't find '%s' in dictionary\n", opt);
		}
	}
}
