gkm_object_dispose (GObject *obj)
{
	GkmObject *self = GKM_OBJECT (obj);
	GkmObjectTransient *transient;

	if (self->pv->manager) {
		if (self->pv->exposed)
			gkm_object_expose (self, FALSE);
		g_return_if_fail (!self->pv->exposed);
		g_object_remove_weak_pointer (G_OBJECT (self->pv->manager),
		                              (gpointer*)&(self->pv->manager));
		self->pv->manager = NULL;
	}

	g_object_set (self, "store", NULL, NULL);
	g_assert (self->pv->store == NULL);

	if (self->pv->transient) {
		transient = self->pv->transient;
		if (transient->timer)
			gkm_timer_cancel (transient->timer);
		transient->timer = NULL;
	}

	G_OBJECT_CLASS (gkm_object_parent_class)->dispose (obj);
}
