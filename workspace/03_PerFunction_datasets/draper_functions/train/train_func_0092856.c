reg_page_map_set(struct i2c_client *client, const u16 reg)
{
	int ret;
	u16 page;
	struct mt9m111 *mt9m111 = to_mt9m111(client);

	page = (reg >> 8);
	if (page == mt9m111->lastpage)
		return 0;
	if (page > 2)
		return -EINVAL;

	ret = i2c_smbus_write_word_swapped(client, MT9M111_PAGE_MAP, page);
	if (!ret)
		mt9m111->lastpage = page;
	return ret;
}
