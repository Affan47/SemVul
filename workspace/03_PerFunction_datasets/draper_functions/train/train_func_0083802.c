parse_element_value(const struct cafebabe_class *klass, struct cafebabe_element_value *e_value)
{
	struct vm_object *ret;

	switch (e_value->tag) {
	case ELEMENT_TYPE_BYTE: {
		jint value;

		if (cafebabe_class_constant_get_integer(klass, e_value->value.const_value_index, &value))
			goto error_out;

		ret		= byte_to_object(value);
		break;
	}
	case ELEMENT_TYPE_CHAR: {
		jint value;

		if (cafebabe_class_constant_get_integer(klass, e_value->value.const_value_index, &value))
			goto error_out;

		ret		= char_to_object(value);
		break;
	}
	case ELEMENT_TYPE_DOUBLE: {
		jdouble value;

		if (cafebabe_class_constant_get_double(klass, e_value->value.const_value_index, &value))
			goto error_out;

		ret		= double_to_object(value);
		break;
	}
	case ELEMENT_TYPE_FLOAT: {
		jfloat value;

		if (cafebabe_class_constant_get_float(klass, e_value->value.const_value_index, &value))
			goto error_out;

		ret		= float_to_object(value);
		break;
	}
	case ELEMENT_TYPE_INTEGER: {
		jint value;

		if (cafebabe_class_constant_get_integer(klass, e_value->value.const_value_index, &value))
			goto error_out;

		ret		= int_to_object(value);
		break;
	}
	case ELEMENT_TYPE_LONG: {
		jlong value;

		if (cafebabe_class_constant_get_long(klass, e_value->value.const_value_index, &value))
			goto error_out;

		ret		= long_to_object(value);
		break;
	}
	case ELEMENT_TYPE_SHORT: {
		jint value;

		if (cafebabe_class_constant_get_integer(klass, e_value->value.const_value_index, &value))
			goto error_out;

		ret		= short_to_object(value);
		break;
	}
	case ELEMENT_TYPE_BOOLEAN: {
		jint value;

		if (cafebabe_class_constant_get_integer(klass, e_value->value.const_value_index, &value))
			goto error_out;

		ret		= boolean_to_object(value);
		break;
	}
	case ELEMENT_TYPE_STRING: {
		const struct cafebabe_constant_info_utf8 *utf8;
		struct vm_object *string;

		if (cafebabe_class_constant_get_utf8(klass, e_value->value.const_value_index, &utf8))
			goto error_out;

		string = vm_object_alloc_string_from_utf8(utf8->bytes, utf8->length);
		if (!string)
			goto error_out;

		ret		= string;
		break;
	}
	case ELEMENT_TYPE_ENUM_CONSTANT:
		ret		= NULL;
		break;
	case ELEMENT_TYPE_CLASS:
		ret		= NULL;
		break;
	case ELEMENT_TYPE_ANNOTATION_TYPE: {
		struct vm_annotation *child_vma;

		child_vma	= vm_annotation_parse(klass, e_value->value.annotation_value);
		if (!child_vma)
			goto error_out;

		ret	= vm_annotation_to_object(child_vma);
		if (!ret)
			goto error_out;
		break;
	}
	case ELEMENT_TYPE_ARRAY: {
		ret		= parse_array_element(klass, e_value);
		break;
	}
	default:
		warn("'%c' is an unknown element value pair tag", e_value->tag);
		goto error_out;
	}

	return ret;

error_out:
	return NULL;
}
