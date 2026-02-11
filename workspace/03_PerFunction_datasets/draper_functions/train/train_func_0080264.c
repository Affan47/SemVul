match_fstype(const struct mntent *mt, const char *t_fstype)
{
	int match = 1;
	int len;

	if (!t_fstype)
		return match;

	if (t_fstype[0] == 'n' && t_fstype[1] == 'o') {
		match--;
		t_fstype += 2;
	}

	len = strlen(mt->mnt_type);
	while (1) {
		if (strncmp(mt->mnt_type, t_fstype, len) == 0
		 && (t_fstype[len] == '\0' || t_fstype[len] == ',')
		) {
			return match;
		}
		t_fstype = strchr(t_fstype, ',');
		if (!t_fstype)
			break;
		t_fstype++;
	}

	return !match;
}
