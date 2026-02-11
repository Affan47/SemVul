hfsplus_remount(struct super_block *sb, int *flags, char *data)
{
	sync_filesystem(sb);
	if ((*flags & MS_RDONLY) == (sb->s_flags & MS_RDONLY))
		return 0;
	if (!(*flags & MS_RDONLY)) {
		struct hfsplus_vh *vhdr = HFSPLUS_SB(sb)->s_vhdr;
		int force = 0;

		if (!hfsplus_parse_options_remount(data, &force))
			return -EINVAL;

		if (!(vhdr->attributes & cpu_to_be32(HFSPLUS_VOL_UNMNT))) {
			pr_warn("filesystem was not cleanly unmounted, running fsck.hfsplus is recommended.  leaving read-only.\n");
			sb->s_flags |= MS_RDONLY;
			*flags |= MS_RDONLY;
		} else if (force) {

		} else if (vhdr->attributes &
				cpu_to_be32(HFSPLUS_VOL_SOFTLOCK)) {
			pr_warn("filesystem is marked locked, leaving read-only.\n");
			sb->s_flags |= MS_RDONLY;
			*flags |= MS_RDONLY;
		} else if (vhdr->attributes &
				cpu_to_be32(HFSPLUS_VOL_JOURNALED)) {
			pr_warn("filesystem is marked journaled, leaving read-only.\n");
			sb->s_flags |= MS_RDONLY;
			*flags |= MS_RDONLY;
		}
	}
	return 0;
}
