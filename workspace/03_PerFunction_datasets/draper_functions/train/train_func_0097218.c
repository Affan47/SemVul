__midgard_user_logout (MidgardUser *self)
{
	g_return_val_if_fail(self != NULL, FALSE);
	g_return_val_if_fail(MIDGARD_IS_USER (self), FALSE);

	MidgardConnection *mgd = MGD_OBJECT_CNC (self);
	g_return_val_if_fail(mgd != NULL, FALSE);

	MIDGARD_ERRNO_SET(mgd, MGD_ERR_OK);

	GSList *list = mgd->priv->authstack;

	if (list == NULL || (list && g_slist_length(list) < 1)) {
		MIDGARD_ERRNO_SET(mgd, MGD_ERR_INTERNAL);
		return FALSE;
	}

	if ((gpointer)self == (gpointer)mgd->priv->user) {
		mgd->priv->authstack = g_slist_remove(mgd->priv->authstack, (gconstpointer) self);

		self->priv->is_logged = FALSE;
		g_object_unref(self);

		g_object_unref(mgd->priv->user);
		if (mgd->priv->authstack && mgd->priv->authstack->data) {
			g_object_ref(mgd->priv->authstack->data);
			mgd->priv->user = (gpointer) mgd->priv->authstack->data;
		} else {
			mgd->priv->user = NULL;
		}

		g_signal_emit_by_name(mgd, "auth_changed");

		return TRUE;
	}


	g_warning("Can not log out user who is not currently logged in");
	MIDGARD_ERRNO_SET(mgd, MGD_ERR_INTERNAL);

	return FALSE;
}
