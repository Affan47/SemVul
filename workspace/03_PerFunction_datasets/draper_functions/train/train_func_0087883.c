print_device(struct blkdev_cxt *cxt, struct tt_line *tt_parent)
{
	int i;

	cxt->tt_line = tt_add_line(lsblk->tt, tt_parent);

	for (i = 0; i < ncolumns; i++)
		set_tt_data(cxt, i, get_column_id(i), cxt->tt_line);
}
