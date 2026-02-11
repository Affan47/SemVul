path_flags(struct aa_profile *profile, const struct path *path)
{
	AA_BUG(!profile);
	AA_BUG(!path);

	return profile->path_flags |
		(S_ISDIR(path->dentry->d_inode->i_mode) ? PATH_IS_DIR : 0);
}
