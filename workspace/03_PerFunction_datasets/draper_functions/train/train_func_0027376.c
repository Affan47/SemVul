ignore(struct fs_info *fs)
{


	if (fs->passno == 0)
		return 1;


	if (!fs_match(fs))
		return 1;


	if (index_in_strings(ignored_types, fs->type) >= 0)
		return 1;


	return 0;
}
