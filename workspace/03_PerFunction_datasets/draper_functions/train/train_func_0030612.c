pk_repo_signature_required_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	PkRepoSignatureRequired *repo_signature_required = PK_REPO_SIGNATURE_REQUIRED (object);
	PkRepoSignatureRequiredPrivate *priv = repo_signature_required->priv;

	switch (prop_id) {
	case PROP_PACKAGE_ID:
		g_value_set_string (value, priv->package_id);
		break;
	case PROP_REPOSITORY_NAME:
		g_value_set_string (value, priv->repository_name);
		break;
	case PROP_KEY_URL:
		g_value_set_string (value, priv->key_url);
		break;
	case PROP_KEY_USERID:
		g_value_set_string (value, priv->key_userid);
		break;
	case PROP_KEY_ID:
		g_value_set_string (value, priv->key_id);
		break;
	case PROP_KEY_FINGERPRINT:
		g_value_set_string (value, priv->key_fingerprint);
		break;
	case PROP_KEY_TIMESTAMP:
		g_value_set_string (value, priv->key_timestamp);
		break;
	case PROP_TYPE:
		g_value_set_uint (value, priv->type);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
