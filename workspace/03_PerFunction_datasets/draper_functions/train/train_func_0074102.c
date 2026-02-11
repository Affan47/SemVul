ext4_add_complete_io(ext4_io_end_t *io_end)
{
	struct ext4_inode_info *ei = EXT4_I(io_end->inode);
	struct ext4_sb_info *sbi = EXT4_SB(io_end->inode->i_sb);
	struct workqueue_struct *wq;
	unsigned long flags;


	WARN_ON(!(io_end->flag & EXT4_IO_END_UNWRITTEN));
	WARN_ON(!io_end->handle && sbi->s_journal);
	spin_lock_irqsave(&ei->i_completed_io_lock, flags);
	wq = sbi->rsv_conversion_wq;
	if (list_empty(&ei->i_rsv_conversion_list))
		queue_work(wq, &ei->i_rsv_conversion_work);
	list_add_tail(&io_end->list, &ei->i_rsv_conversion_list);
	spin_unlock_irqrestore(&ei->i_completed_io_lock, flags);
}
