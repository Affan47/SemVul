logfs_handle_transaction(struct inode *inode,
		struct logfs_transaction *ta)
{
	struct logfs_super *super = logfs_super(inode->i_sb);

	if (!ta)
		return;
	logfs_inode(inode)->li_block->ta = NULL;

	if (inode->i_ino != LOGFS_INO_MASTER) {
		BUG();


		return;
	}

	switch (ta->state) {
	case CREATE_1:
	case UNLINK_1:
		BUG_ON(super->s_victim_ino);
		super->s_victim_ino = ta->ino;
		break;
	case CREATE_2:
	case UNLINK_2:
		BUG_ON(super->s_victim_ino != ta->ino);
		super->s_victim_ino = 0;

		kfree(ta);
		break;
	case CROSS_RENAME_1:
		BUG_ON(super->s_rename_dir);
		BUG_ON(super->s_rename_pos);
		super->s_rename_dir = ta->dir;
		super->s_rename_pos = ta->pos;
		break;
	case CROSS_RENAME_2:
		BUG_ON(super->s_rename_dir != ta->dir);
		BUG_ON(super->s_rename_pos != ta->pos);
		super->s_rename_dir = 0;
		super->s_rename_pos = 0;
		kfree(ta);
		break;
	case TARGET_RENAME_1:
		BUG_ON(super->s_rename_dir);
		BUG_ON(super->s_rename_pos);
		BUG_ON(super->s_victim_ino);
		super->s_rename_dir = ta->dir;
		super->s_rename_pos = ta->pos;
		super->s_victim_ino = ta->ino;
		break;
	case TARGET_RENAME_2:
		BUG_ON(super->s_rename_dir != ta->dir);
		BUG_ON(super->s_rename_pos != ta->pos);
		BUG_ON(super->s_victim_ino != ta->ino);
		super->s_rename_dir = 0;
		super->s_rename_pos = 0;
		break;
	case TARGET_RENAME_3:
		BUG_ON(super->s_rename_dir);
		BUG_ON(super->s_rename_pos);
		BUG_ON(super->s_victim_ino != ta->ino);
		super->s_victim_ino = 0;
		kfree(ta);
		break;
	default:
		BUG();
	}
}
