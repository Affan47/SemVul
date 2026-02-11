native_field_get(struct vm_object *this, struct vm_object *o)
{
	struct vm_field *vmf;
	enum vm_type type;
	void *value_p;

	vmf = vm_object_to_vm_field(this);
	if (!vmf)
		return NULL;

	type	= vm_field_type(vmf);
	value_p	= field_get_value(vmf, o);
	if (!value_p)
		return NULL;

	return jvalue_to_object((union jvalue *) value_p, type);
}
