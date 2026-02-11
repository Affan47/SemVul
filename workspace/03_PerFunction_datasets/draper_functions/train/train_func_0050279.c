CONNSECMARK_parse(struct xt_option_call *cb)
{
	struct xt_connsecmark_target_info *info = cb->data;

	xtables_option_parse(cb);
	switch (cb->entry->id) {
	case O_SAVE:
		info->mode = CONNSECMARK_SAVE;
		break;
	case O_RESTORE:
		info->mode = CONNSECMARK_RESTORE;
		break;
	}
}
