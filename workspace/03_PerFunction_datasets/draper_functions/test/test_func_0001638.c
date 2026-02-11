to_jfloat_value(union jvalue *value, enum vm_type vm_type)
{
	switch (vm_type) {
	case J_BYTE:
		return value->b;
	case J_SHORT:
		return value->s;
	case J_CHAR:
		return value->c;
	case J_FLOAT:
		return value->f;
	case J_INT:
		return value->i;
	case J_LONG:
		return value->j;
	case J_BOOLEAN:
	case J_DOUBLE:
	case J_REFERENCE: {
		signal_new_exception(vm_java_lang_IllegalArgumentException, NULL);
		return 0;
	}
	case J_RETURN_ADDRESS:
	case J_VOID:
	case VM_TYPE_MAX:
		break;
	}
	die("unexpected type %d", vm_type);
}
