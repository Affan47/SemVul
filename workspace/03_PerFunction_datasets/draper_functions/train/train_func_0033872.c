ubifs_jnl_write_inode(struct ubifs_info *c, const struct inode *inode)
{
	int err, lnum, offs;
	struct ubifs_ino_node *ino;
	struct ubifs_inode *ui = ubifs_inode(inode);
	int sync = 0, len = UBIFS_INO_NODE_SZ, last_reference = !inode->i_nlink;

	dbg_jnl("ino %lu, nlink %u", inode->i_ino, inode->i_nlink);


	if (!last_reference) {
		len += ui->data_len;
		sync = IS_SYNC(inode);
	}
	ino = kmalloc(len, GFP_NOFS);
	if (!ino)
		return -ENOMEM;


	err = make_reservation(c, BASEHD, len);
	if (err)
		goto out_free;

	pack_inode(c, ino, inode, 1);
	err = write_head(c, BASEHD, ino, len, &lnum, &offs, sync);
	if (err)
		goto out_release;
	if (!sync)
		ubifs_wbuf_add_ino_nolock(&c->jheads[BASEHD].wbuf,
					  inode->i_ino);
	release_head(c, BASEHD);

	if (last_reference) {
		err = ubifs_tnc_remove_ino(c, inode->i_ino);
		if (err)
			goto out_ro;
		ubifs_delete_orphan(c, inode->i_ino);
		err = ubifs_add_dirt(c, lnum, len);
	} else {
		union ubifs_key key;

		ino_key_init(c, &key, inode->i_ino);
		err = ubifs_tnc_add(c, &key, lnum, offs, len);
	}
	if (err)
		goto out_ro;

	finish_reservation(c);
	spin_lock(&ui->ui_lock);
	ui->synced_i_size = ui->ui_size;
	spin_unlock(&ui->ui_lock);
	kfree(ino);
	return 0;

out_release:
	release_head(c, BASEHD);
out_ro:
	ubifs_ro_mode(c, err);
	finish_reservation(c);
out_free:
	kfree(ino);
	return err;
}
