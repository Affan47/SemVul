cafebabe_annotations_attribute_init(struct cafebabe_annotations_attribute *a, struct cafebabe_stream *s)
{
	int err = 0;

	err = cafebabe_stream_read_uint16(s, &a->num_annotations);
	if (err)
		goto out;

	if (!a->num_annotations)
		goto out;

	a->annotations = calloc(a->num_annotations, sizeof(struct cafebabe_annotation));
	if (!a->annotations) {
		err = -1;
		goto out;
	}
	for (unsigned int i = 0; i < a->num_annotations; i++) {
		err = cafebabe_annotation_parse(&a->annotations[i], s);
		if (err)
			goto out;
	}
out:
	return err;
}
