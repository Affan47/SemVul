pk_progress_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	PkProgress *progress = PK_PROGRESS (object);

	switch (prop_id) {
	case PROP_PACKAGE_ID:
		g_value_set_string (value, progress->priv->package_id);
		break;
	case PROP_TRANSACTION_ID:
		g_value_set_string (value, progress->priv->transaction_id);
		break;
	case PROP_PERCENTAGE:
		g_value_set_int (value, progress->priv->percentage);
		break;
	case PROP_ITEM_PROGRESS:
		g_value_set_object (value, progress->priv->item_progress);
		break;
	case PROP_ALLOW_CANCEL:
		g_value_set_boolean (value, progress->priv->allow_cancel);
		break;
	case PROP_STATUS:
		g_value_set_uint (value, progress->priv->status);
		break;
	case PROP_ROLE:
		g_value_set_uint (value, progress->priv->role);
		break;
	case PROP_CALLER_ACTIVE:
		g_value_set_boolean (value, progress->priv->caller_active);
		break;
	case PROP_ELAPSED_TIME:
		g_value_set_uint (value, progress->priv->elapsed_time);
		break;
	case PROP_REMAINING_TIME:
		g_value_set_uint (value, progress->priv->remaining_time);
		break;
	case PROP_SPEED:
		g_value_set_uint (value, progress->priv->speed);
		break;
	case PROP_DOWNLOAD_SIZE_REMAINING:
		g_value_set_uint64 (value, progress->priv->download_size_remaining);
		break;
	case PROP_TRANSACTION_FLAGS:
		g_value_set_uint64 (value, progress->priv->transaction_flags);
		break;
	case PROP_UID:
		g_value_set_uint (value, progress->priv->uid);
		break;
	case PROP_PACKAGE:
		g_value_set_object (value, progress->priv->package);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
