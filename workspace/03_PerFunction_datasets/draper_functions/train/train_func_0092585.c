joint_copy_helper(const struct ast_format_cap *cap1, const struct ast_format_cap *cap2, struct ast_format_cap *result, int append)
{
	struct ao2_iterator it;
	struct ast_format *tmp;
	struct find_joint_data data = {
		.joint_cap = result,
		.joint_found = 0,
	};
	if (!append) {
		ast_format_cap_remove_all(result);
	}
	it = ao2_iterator_init(cap1->formats, 0);
	while ((tmp = ao2_iterator_next(&it))) {
		data.format = tmp;
		ao2_callback(cap2->formats,
			OBJ_MULTIPLE | OBJ_NODATA,
			find_joint_cb,
			&data);
		ao2_ref(tmp, -1);
	}
	ao2_iterator_destroy(&it);

	return ao2_container_count(result->formats) ? 1 : 0;
}
