java_lang_VMClassLoader_defineClass(jobject classloader, jobject name,
	jobject data, jint offset, jint len, jobject pd)
{
	struct vm_class *class;
	char *c_name;
	uint8_t *buf;

	buf = malloc(len);
	if (!buf)
		return throw_oom_error();

	for (jint i = 0; i < len; i++)
		buf[i] = array_get_field_byte(data, offset + i);

	if (name)
		c_name = vm_string_to_cstr(name);
	else
		c_name = strdup("unknown");

	class = vm_class_define(classloader, c_name, buf, len);
	free(buf);

	if (!class)
		return rethrow_exception();

	if (classloader_add_to_cache(classloader, class))
		return throw_oom_error();

	if (vm_class_ensure_object(class))
		return rethrow_exception();

	vm_call_method(vm_java_lang_Class_init, class->object, class, pd);
	if (exception_occurred())
		return rethrow_exception();

	return class->object;
}
