cafebabe_read_inner_classes_attribute(const struct cafebabe_class *class,
					     const struct cafebabe_attribute_array *attributes,
					     struct cafebabe_inner_classes_attribute *inner_classes_attrib)
{
	const struct cafebabe_attribute_info *attribute;
	unsigned int inner_classes_index = 0;
	struct cafebabe_stream stream;

	if (cafebabe_attribute_array_get(attributes, "InnerClasses", class, &inner_classes_index))
		return 0;

	attribute = &class->attributes.array[inner_classes_index];

	cafebabe_stream_open_buffer(&stream, attribute->info, attribute->attribute_length);

	if (cafebabe_inner_classes_attribute_init(inner_classes_attrib, &stream))
		return -1;

	cafebabe_stream_close_buffer(&stream);

	return 0;
}
