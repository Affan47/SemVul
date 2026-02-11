store_de_entry_key(struct reiserfs_dir_entry *de)
{
	struct reiserfs_de_head *deh = de->de_deh + de->de_entry_num;

	BUG_ON(de->de_entry_num >= ih_entry_count(de->de_ih));


	de->de_entry_key.version = KEY_FORMAT_3_5;
	de->de_entry_key.on_disk_key.k_dir_id =
	    le32_to_cpu(de->de_ih->ih_key.k_dir_id);
	de->de_entry_key.on_disk_key.k_objectid =
	    le32_to_cpu(de->de_ih->ih_key.k_objectid);
	set_cpu_key_k_offset(&de->de_entry_key, deh_offset(deh));
	set_cpu_key_k_type(&de->de_entry_key, TYPE_DIRENTRY);
}
