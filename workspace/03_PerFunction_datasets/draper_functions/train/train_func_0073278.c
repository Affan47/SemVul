fat_ilookup(struct super_block *sb, u64 ino, loff_t i_pos)
{
	if (MSDOS_SB(sb)->options.nfs == FAT_NFS_NOSTALE_RO)
		return fat_iget(sb, i_pos);

	else {
		if ((ino < MSDOS_ROOT_INO) || (ino == MSDOS_FSINFO_INO))
			return NULL;
		return ilookup(sb, ino);
	}
}
