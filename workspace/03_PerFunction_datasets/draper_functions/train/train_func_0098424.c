spi_register_board_info(struct spi_board_info const *info, unsigned n)
{
	struct boardinfo *bi;
	int i;

	if (!n)
		return -EINVAL;

	bi = kzalloc(n * sizeof(*bi), GFP_KERNEL);
	if (!bi)
		return -ENOMEM;

	for (i = 0; i < n; i++, bi++, info++) {
		struct spi_master *master;

		memcpy(&bi->board_info, info, sizeof(*info));
		mutex_lock(&board_lock);
		list_add_tail(&bi->list, &board_list);
		list_for_each_entry(master, &spi_master_list, list)
			spi_match_master_to_boardinfo(master, &bi->board_info);
		mutex_unlock(&board_lock);
	}

	return 0;
}
