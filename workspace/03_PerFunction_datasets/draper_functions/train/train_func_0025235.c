tproxy_tg1_parse(struct xt_option_call *cb)
{
	struct xt_tproxy_target_info_v1 *info = cb->data;

	xtables_option_parse(cb);
	switch (cb->entry->id) {
	case P_MARK:
		info->mark_value = cb->val.mark;
		info->mark_mask  = cb->val.mask;
		break;
	}
}
