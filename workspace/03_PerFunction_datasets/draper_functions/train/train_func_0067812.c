bt_ctf_field_type_variant_destroy(struct bt_ctf_ref *ref)
{
	struct bt_ctf_field_type_variant *variant;

	if (!ref) {
		return;
	}

	variant = container_of(
		container_of(ref, struct bt_ctf_field_type, ref_count),
		struct bt_ctf_field_type_variant, parent);
	g_ptr_array_free(variant->fields, TRUE);
	g_hash_table_destroy(variant->field_name_to_index);
	g_string_free(variant->tag_name, TRUE);
	bt_ctf_field_type_put(&variant->tag->parent);
	g_free(variant);
}
