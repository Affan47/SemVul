swan_vk_show_key_table(const struct swan_vk_descriptor *descs, size_t size)
{
	const struct swan_vk_descriptor *desc_end;

	for (desc_end = descs + size; descs < desc_end; descs++)
	{
		println("%s = %d", descs->name, descs->code);
	}
}
