cavan_ext4_dump_gdt(struct cavan_ext4_fs *fs)
{
	int i;

	if (fs->gdt32)
	{
		for (i = 0; i < (int) fs->group_count; i++)
		{
			cavan_ext4_dump_ext2_group_desc(fs->gdt32 + i);
			println("index = %d", i);
		}
	}
	else
	{
		for (i = 0; i < (int) fs->group_count; i++)
		{
			cavan_ext4_dump_ext4_group_desc(fs->gdt64 + i);
			println("index = %d", i);
		}
	}
}
