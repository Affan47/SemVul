map_old_perms(u32 old)
{
	u32 new = old & 0xf;
	if (old & MAY_READ)
		new |= AA_MAY_GETATTR | AA_MAY_OPEN;
	if (old & MAY_WRITE)
		new |= AA_MAY_SETATTR | AA_MAY_CREATE | AA_MAY_DELETE |
			AA_MAY_CHMOD | AA_MAY_CHOWN | AA_MAY_OPEN |
		        AA_MAY_DELETE;
	if (old & 0x10)
		new |= AA_MAY_LINK;


	if (old & 0x20)
		new |= AA_MAY_LOCK | AA_LINK_SUBSET;
	if (old & 0x40)
		new |= AA_EXEC_MMAP;

	return new;
}
