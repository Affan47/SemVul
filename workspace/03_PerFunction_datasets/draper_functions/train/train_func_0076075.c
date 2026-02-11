cafebabe_read_annotations_attribute(const struct cafebabe_class *class,
				    const struct cafebabe_attribute_array *attributes,
				    struct cafebabe_annotations_attribute *annotations_attrib)
{
	const struct cafebabe_attribute_info *attribute;
	unsigned int annotations_index = 0;
	struct cafebabe_stream stream;
	int err;

	memset(annotations_attrib, 0, sizeof(*annotations_attrib));

	if (cafebabe_attribute_array_get(attributes, "RuntimeVisibleAnnotations", class, &annotations_index))
		return 0;

	attribute = &attributes->array[annotations_index];

	cafebabe_stream_open_buffer(&stream, attribute->info, attribute->attribute_length);

	err = cafebabe_annotations_attribute_init(annotations_attrib, &stream);

	cafebabe_stream_close_buffer(&stream);

	return err;
}
