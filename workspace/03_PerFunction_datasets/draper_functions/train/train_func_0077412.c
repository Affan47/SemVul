xfs_default_resblks(xfs_mount_t *mp)
{
	__uint64_t resblks;


	resblks = mp->m_sb.sb_dblocks;
	do_div(resblks, 20);
	resblks = min_t(__uint64_t, resblks, 8192);
	return resblks;
}
