_g_file_attribute_value_free (_GFileAttributeValue *attr_value)
{
	switch (attr_value->type) {
	case G_FILE_ATTRIBUTE_TYPE_STRING:
	case G_FILE_ATTRIBUTE_TYPE_BYTE_STRING:
		g_free (attr_value->v.string);
		break;
#if GLIB_CHECK_VERSION(2,22,0)
	case G_FILE_ATTRIBUTE_TYPE_STRINGV:
		g_strfreev (attr_value->v.stringv);
		break;
#endif
	case G_FILE_ATTRIBUTE_TYPE_OBJECT:
		g_object_unref (attr_value->v.object);
		break;
	default:
		break;
	}

	g_free (attr_value);
}
