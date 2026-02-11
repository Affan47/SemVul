u32_save(const void *ip, const struct xt_entry_match *match)
{
	const struct xt_u32 *data = (const void *)match->data;
	if (data->invert)
		printf(" !");
	printf(" --u32");
	u32_dump(data);
}
