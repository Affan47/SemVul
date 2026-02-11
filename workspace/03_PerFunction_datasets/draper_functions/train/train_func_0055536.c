gda_tree_mgr_label_set_property (GObject *object,
				   guint param_id,
				   const GValue *value,
				   GParamSpec *pspec)
{
        GdaTreeMgrLabel *mgr;

        mgr = GDA_TREE_MGR_LABEL (object);
        if (mgr->priv) {
                switch (param_id) {
		case PROP_LABEL:
			mgr->priv->label = g_value_dup_string (value);
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
			break;
                }
        }
}
