sx150x_io_output(struct sx150x_chip *chip, unsigned offset, int val)
{
	int err;

	err = sx150x_write_cfg(chip,
			offset,
			1,
			chip->dev_cfg->reg_data,
			(val ? 1 : 0));
	if (err >= 0)
		err = sx150x_write_cfg(chip,
				offset,
				1,
				chip->dev_cfg->reg_dir,
				0);
	return err;
}
