tos_mt_parse_v0(int c, char **argv, int invert, unsigned int *flags,
                           const void *entry, struct xt_entry_match **match)
{
	struct ipt_tos_info *info = (void *)(*match)->data;
	struct tos_value_mask tvm;

	switch (c) {
	case 't':
		xtables_param_act(XTF_ONLY_ONCE, "tos", "--tos", *flags & FLAG_TOS);
		if (!tos_parse_symbolic(optarg, &tvm, 0xFF))
			xtables_param_act(XTF_BAD_VALUE, "tos", "--tos", optarg);
		if (tvm.mask != 0xFF)
			xtables_error(PARAMETER_PROBLEM, "tos: Your kernel is "
			           "too old to support anything besides /0xFF "
				   "as a mask.");
		info->tos = tvm.value;
		if (invert)
			info->invert = true;
		*flags |= FLAG_TOS;
		return true;
	}
	return false;
}
