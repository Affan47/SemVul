ubifs_fixup_free_space(struct ubifs_info *c)
{
	int err;
	struct ubifs_sb_node *sup;

	ubifs_assert(c->space_fixup);
	ubifs_assert(!c->ro_mount);

	ubifs_msg(c, "start fixing up free space");

	err = fixup_free_space(c);
	if (err)
		return err;

	sup = ubifs_read_sb_node(c);
	if (IS_ERR(sup))
		return PTR_ERR(sup);


	c->space_fixup = 0;
	sup->flags &= cpu_to_le32(~UBIFS_FLG_SPACE_FIXUP);

	err = ubifs_write_sb_node(c, sup);
	kfree(sup);
	if (err)
		return err;

	ubifs_msg(c, "free space fixup complete");
	return err;
}
