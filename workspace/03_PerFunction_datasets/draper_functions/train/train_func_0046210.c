value_transform_string_enum(const GValue *src_value, GValue *dest_value) {
    GEnumClass *klass = g_type_class_ref(G_VALUE_TYPE(dest_value));
    GEnumValue *enum_value = g_enum_get_value_by_name(klass, src_value->data[0].v_pointer);

    if (enum_value)
	dest_value->data[0].v_int = enum_value->value;
    else
	dest_value->data[0].v_int = 0;

    g_type_class_unref(klass);
}
