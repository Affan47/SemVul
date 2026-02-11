connmark_mt_parse(int c, char **argv, int invert, unsigned int *flags,
                  const void *entry, struct xt_entry_match **match)
{
	struct xt_connmark_mtinfo1 *info = (void *)(*match)->data;
	unsigned int mark, mask = UINT32_MAX;
	char *end;

	switch (c) {
	case '1':
		xtables_param_act(XTF_ONLY_ONCE, "connmark", "--mark", *flags & F_MARK);
		if (!xtables_strtoui(optarg, &end, &mark, 0, UINT32_MAX))
			xtables_param_act(XTF_BAD_VALUE, "connmark", "--mark", optarg);
		if (*end == '/')
			if (!xtables_strtoui(end + 1, &end, &mask, 0, UINT32_MAX))
				xtables_param_act(XTF_BAD_VALUE, "connmark", "--mark", optarg);
		if (*end != '\0')
			xtables_param_act(XTF_BAD_VALUE, "connmark", "--mark", optarg);

		if (invert)
			info->invert = true;
		info->mark = mark;
		info->mask = mask;
		*flags    |= F_MARK;
		return true;
	}
	return false;
}
