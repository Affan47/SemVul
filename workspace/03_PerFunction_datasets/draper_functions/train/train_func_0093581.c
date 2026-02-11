go_file_saver_set_property (GObject *object, guint property_id,
			    GValue const *value, GParamSpec *pspec)
{
	GOFileSaver *fs = (GOFileSaver *)object;

	switch (property_id) {
	case FS_PROP_ID: {
		char *s = g_value_dup_string (value);
		g_free (fs->id);
		fs->id = s;
		break;
	}
	case FS_PROP_MIME_TYPE: {
		char *s = g_value_dup_string (value);
		g_free (fs->mime_type);
		fs->mime_type = s;
		break;
	}
	case FS_PROP_EXTENSION: {
		char *s = g_value_dup_string (value);
		g_free (fs->extension);
		fs->extension = s;
		break;
	}
	case FS_PROP_DESCRIPTION: {
		char *s = g_value_dup_string (value);
		g_free (fs->description);
		fs->description = s;
		break;
	}
	case FS_PROP_OVERWRITE:
		fs->overwrite_files = g_value_get_boolean (value);
		break;
	case FS_PROP_INTERACTIVE_ONLY:
		fs->interactive_only = g_value_get_boolean (value);
		break;
	case FS_PROP_FORMAT_LEVEL:
		fs->format_level = g_value_get_enum (value);
		break;
	case FS_PROP_SCOPE:
		fs->save_scope = g_value_get_enum (value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
