_g_file_info_set_value (GFileInfo            *info,
			const char           *attr,
			_GFileAttributeValue *attr_value)
{
	gpointer value = NULL;

	if (attr_value->type == G_FILE_ATTRIBUTE_TYPE_INVALID)
		return;

	switch (attr_value->type) {
	case G_FILE_ATTRIBUTE_TYPE_STRING:
	case G_FILE_ATTRIBUTE_TYPE_BYTE_STRING:
		value = attr_value->v.string;
		break;


	case G_FILE_ATTRIBUTE_TYPE_BOOLEAN:
		value = &attr_value->v.boolean;
		break;
	case G_FILE_ATTRIBUTE_TYPE_UINT32:
		value = &attr_value->v.uint32;
		break;
	case G_FILE_ATTRIBUTE_TYPE_INT32:
		value = &attr_value->v.int32;
		break;
	case G_FILE_ATTRIBUTE_TYPE_UINT64:
		value = &attr_value->v.uint64;
		break;
	case G_FILE_ATTRIBUTE_TYPE_INT64:
		value = &attr_value->v.int64;
		break;
	case G_FILE_ATTRIBUTE_TYPE_OBJECT:
		value = attr_value->v.object;
		break;
	default:
		g_warning ("Unknown attribute type: %d", attr_value->type);
		break;
	}

	g_file_info_set_attribute (info, attr, attr_value->type, value);
}
