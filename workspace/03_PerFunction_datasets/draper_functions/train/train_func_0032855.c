tomoyo_read_profile(struct tomoyo_io_buffer *head)
{
	u8 index;
	struct tomoyo_policy_namespace *ns =
		container_of(head->r.ns, typeof(*ns), namespace_list);
	const struct tomoyo_profile *profile;
	if (head->r.eof)
		return;
 next:
	index = head->r.index;
	profile = ns->profile_ptr[index];
	switch (head->r.step) {
	case 0:
		tomoyo_print_namespace(head);
		tomoyo_io_printf(head, "PROFILE_VERSION=%u\n",
				 ns->profile_version);
		head->r.step++;
		break;
	case 1:
		for ( ; head->r.index < TOMOYO_MAX_PROFILES;
		      head->r.index++)
			if (ns->profile_ptr[head->r.index])
				break;
		if (head->r.index == TOMOYO_MAX_PROFILES) {
			head->r.eof = true;
			return;
		}
		head->r.step++;
		break;
	case 2:
		{
			u8 i;
			const struct tomoyo_path_info *comment =
				profile->comment;
			tomoyo_print_namespace(head);
			tomoyo_io_printf(head, "%u-COMMENT=", index);
			tomoyo_set_string(head, comment ? comment->name : "");
			tomoyo_set_lf(head);
			tomoyo_print_namespace(head);
			tomoyo_io_printf(head, "%u-PREFERENCE={ ", index);
			for (i = 0; i < TOMOYO_MAX_PREF; i++)
				tomoyo_io_printf(head, "%s=%u ",
						 tomoyo_pref_keywords[i],
						 profile->pref[i]);
			tomoyo_set_string(head, "}\n");
			head->r.step++;
		}
		break;
	case 3:
		{
			tomoyo_print_namespace(head);
			tomoyo_io_printf(head, "%u-%s", index, "CONFIG");
			tomoyo_print_config(head, profile->default_config);
			head->r.bit = 0;
			head->r.step++;
		}
		break;
	case 4:
		for ( ; head->r.bit < TOMOYO_MAX_MAC_INDEX
			      + TOMOYO_MAX_MAC_CATEGORY_INDEX; head->r.bit++) {
			const u8 i = head->r.bit;
			const u8 config = profile->config[i];
			if (config == TOMOYO_CONFIG_USE_DEFAULT)
				continue;
			tomoyo_print_namespace(head);
			if (i < TOMOYO_MAX_MAC_INDEX)
				tomoyo_io_printf(head, "%u-CONFIG::%s::%s",
						 index,
						 tomoyo_category_keywords
						 [tomoyo_index2category[i]],
						 tomoyo_mac_keywords[i]);
			else
				tomoyo_io_printf(head, "%u-CONFIG::%s", index,
						 tomoyo_mac_keywords[i]);
			tomoyo_print_config(head, config);
			head->r.bit++;
			break;
		}
		if (head->r.bit == TOMOYO_MAX_MAC_INDEX
		    + TOMOYO_MAX_MAC_CATEGORY_INDEX) {
			head->r.index++;
			head->r.step = 1;
		}
		break;
	}
	if (tomoyo_flush(head))
		goto next;
}
