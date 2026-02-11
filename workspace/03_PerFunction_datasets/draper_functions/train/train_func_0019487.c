vm_annotation_get_type(struct vm_annotation *vma)
{
	struct vm_class *klass = NULL;
	struct vm_type_info type;
	char *buf, *type_name;

	buf = type_name = strdup(vma->type);
	if (!type_name)
		goto out;

	if (parse_type(&type_name, &type))
		goto out;

	klass = classloader_load(get_system_class_loader(), type.class_name);
	if (!klass)
		return rethrow_exception();
out:
	free(buf);
	return klass;
}
