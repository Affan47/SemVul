gkd_secret_objects_dispose (GObject *obj)
{
	GkdSecretObjects *self = GKD_SECRET_OBJECTS (obj);

	if (self->pkcs11_slot) {
		g_object_unref (self->pkcs11_slot);
		self->pkcs11_slot = NULL;
	}

	if (self->service) {
		g_object_remove_weak_pointer (G_OBJECT (self->service),
		                              (gpointer*)&(self->service));
		self->service = NULL;
	}

	G_OBJECT_CLASS (gkd_secret_objects_parent_class)->dispose (obj);
}
