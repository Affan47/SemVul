soc_tplg_check_elem_count(struct soc_tplg *tplg, size_t elem_size,
	unsigned int count, size_t bytes, const char *elem_type)
{
	const u8 *end = tplg->pos + elem_size * count;

	if (end > tplg->fw->data + tplg->fw->size) {
		dev_err(tplg->dev, "ASoC: %s overflow end of data\n",
			elem_type);
		return -EINVAL;
	}


	if (elem_size * count > bytes) {
		dev_err(tplg->dev,
			"ASoC: %s count %d of size %zu is bigger than chunk %zu\n",
			elem_type, count, elem_size, bytes);
		return -EINVAL;
	}

	return 0;
}
