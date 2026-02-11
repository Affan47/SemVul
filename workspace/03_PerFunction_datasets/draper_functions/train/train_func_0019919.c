gkm_gnome2_private_key_finalize (GObject *obj)
{
	GkmGnome2PrivateKey *self = GKM_GNOME2_PRIVATE_KEY (obj);

	g_assert (self->login == NULL);

	if (self->private_bytes)
		g_bytes_unref (self->private_bytes);

	if (self->private_sexp)
		gkm_sexp_unref (self->private_sexp);
	self->private_sexp = NULL;

	G_OBJECT_CLASS (gkm_gnome2_private_key_parent_class)->finalize (obj);
}
