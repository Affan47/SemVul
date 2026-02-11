mono_field_resolve_flags (MonoClassField *field)
{
	MonoClass *class = field->parent;
	MonoImage *image = class->image;
	MonoClass *gtd = class->generic_class ? mono_class_get_generic_type_definition (class) : NULL;
	int field_idx = field - class->fields;


	if (gtd) {
		MonoClassField *gfield = &gtd->fields [field_idx];
		return mono_field_get_flags (gfield);
	} else {
		int idx = class->field.first + field_idx;


		g_assert (!image->dynamic);

		return mono_metadata_decode_table_row_col (image, MONO_TABLE_FIELD, idx, MONO_FIELD_FLAGS);
	}
}
