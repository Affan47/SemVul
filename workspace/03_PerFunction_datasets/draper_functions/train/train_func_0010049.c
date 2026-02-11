_g_file_info_get_value (GFileInfo  *info,
			const char *attr)
{
	_GFileAttributeValue  *attr_value;
	GFileAttributeType     type;
	gpointer               value;
	GFileAttributeStatus   status;

	attr_value = g_new (_GFileAttributeValue, 1);
	attr_value->type = G_FILE_ATTRIBUTE_TYPE_INVALID;

	if (! g_file_info_get_attribute_data (info, attr, &type, &value, &status))
		return attr_value;

	attr_value->type = type;
	switch (type) {
	case G_FILE_ATTRIBUTE_TYPE_INVALID:
		break;
	case G_FILE_ATTRIBUTE_TYPE_STRING:
	case G_FILE_ATTRIBUTE_TYPE_BYTE_STRING:
		attr_value->v.string = g_strdup ((char *) value);
		break;


	case G_FILE_ATTRIBUTE_TYPE_BOOLEAN:
		attr_value->v.boolean = * ((gboolean *) value);
		break;
	case G_FILE_ATTRIBUTE_TYPE_UINT32:
		attr_value->v.uint32 = * ((guint32 *) value);
		break;
	case G_FILE_ATTRIBUTE_TYPE_INT32:
		attr_value->v.int32 = * ((gint32 *) value);
		break;
	case G_FILE_ATTRIBUTE_TYPE_UINT64:
		attr_value->v.uint64 = * ((guint64 *) value);
		break;
	case G_FILE_ATTRIBUTE_TYPE_INT64:
		attr_value->v.int64 = * ((gint64 *) value);
		break;
	case G_FILE_ATTRIBUTE_TYPE_OBJECT:
		attr_value->v.object = g_object_ref ((GObject *) value);
		break;
	default:
		g_warning ("unknown attribute type: %d", type);
		break;
	}

	return attr_value;
}
