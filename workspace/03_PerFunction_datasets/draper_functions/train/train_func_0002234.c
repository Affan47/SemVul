gck_object_set_property (GObject *obj, guint prop_id, const GValue *value,
                         GParamSpec *pspec)
{
	GckObject *self = GCK_OBJECT (obj);


	switch (prop_id) {
	case PROP_MODULE:
		g_return_if_fail (!self->pv->module);
		self->pv->module = g_value_get_object (value);
		g_return_if_fail (self->pv->module);
		g_object_ref (self->pv->module);
		break;
	case PROP_SESSION:
		g_return_if_fail (!self->pv->session);
		self->pv->session = g_value_get_object (value);
		g_return_if_fail (self->pv->session);
		g_object_ref (self->pv->session);
		break;
	case PROP_HANDLE:
		g_return_if_fail (!self->pv->handle);
		self->pv->handle = g_value_get_ulong (value);
		break;
	}
}
