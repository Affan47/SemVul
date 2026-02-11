mfd_cell_disable(struct platform_device *pdev)
{
	const struct mfd_cell *cell = mfd_get_cell(pdev);
	int err = 0;


	if (atomic_dec_return(cell->usage_count) == 0)
		err = cell->disable(pdev);


	if (err)
		atomic_inc(cell->usage_count);


	WARN_ON(atomic_read(cell->usage_count) < 0);

	return err;
}
