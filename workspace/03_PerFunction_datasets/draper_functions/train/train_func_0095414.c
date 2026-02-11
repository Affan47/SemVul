mlx4_WRITE_MTT_wrapper(struct mlx4_dev *dev, int slave,
			   struct mlx4_vhcr *vhcr,
			   struct mlx4_cmd_mailbox *inbox,
			   struct mlx4_cmd_mailbox *outbox,
			   struct mlx4_cmd_info *cmd)
{
	struct mlx4_mtt mtt;
	__be64 *page_list = inbox->buf;
	u64 *pg_list = (u64 *)page_list;
	int i;
	struct res_mtt *rmtt = NULL;
	int start = be64_to_cpu(page_list[0]);
	int npages = vhcr->in_modifier;
	int err;

	err = get_containing_mtt(dev, slave, start, npages, &rmtt);
	if (err)
		return err;


	mtt.offset = 0;

	mtt.order = 0;
	mtt.page_shift = 0;
	for (i = 0; i < npages; ++i)
		pg_list[i + 2] = (be64_to_cpu(page_list[i + 2]) & ~1ULL);

	err = __mlx4_write_mtt(dev, &mtt, be64_to_cpu(page_list[0]), npages,
			       ((u64 *)page_list + 2));

	if (rmtt)
		put_res(dev, slave, rmtt->com.res_id, RES_MTT);

	return err;
}
