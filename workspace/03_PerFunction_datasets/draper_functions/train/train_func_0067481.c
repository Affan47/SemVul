regmap_ibt_write(void *context, const void *data, size_t count)
{


	if (WARN_ONCE(count < 4, "Invalid register access"))
		return -EINVAL;

	return regmap_ibt_gather_write(context, data, 4, data + 4, count - 4);
}
