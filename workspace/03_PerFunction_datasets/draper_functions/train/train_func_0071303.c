tomoyo_write_profile(struct tomoyo_io_buffer *head)
{
	char *data = head->write_buf;
	unsigned int i;
	char *cp;
	struct tomoyo_profile *profile;
	if (sscanf(data, "PROFILE_VERSION=%u", &head->w.ns->profile_version)
	    == 1)
		return 0;
	i = simple_strtoul(data, &cp, 10);
	if (*cp != '-')
		return -EINVAL;
	data = cp + 1;
	profile = tomoyo_assign_profile(head->w.ns, i);
	if (!profile)
		return -EINVAL;
	cp = strchr(data, '=');
	if (!cp)
		return -EINVAL;
	*cp++ = '\0';
	if (!strcmp(data, "COMMENT")) {
		static DEFINE_SPINLOCK(lock);
		const struct tomoyo_path_info *new_comment
			= tomoyo_get_name(cp);
		const struct tomoyo_path_info *old_comment;
		if (!new_comment)
			return -ENOMEM;
		spin_lock(&lock);
		old_comment = profile->comment;
		profile->comment = new_comment;
		spin_unlock(&lock);
		tomoyo_put_name(old_comment);
		return 0;
	}
	if (!strcmp(data, "PREFERENCE")) {
		for (i = 0; i < TOMOYO_MAX_PREF; i++)
			tomoyo_set_uint(&profile->pref[i], cp,
					tomoyo_pref_keywords[i]);
		return 0;
	}
	return tomoyo_set_mode(data, cp, profile);
}
