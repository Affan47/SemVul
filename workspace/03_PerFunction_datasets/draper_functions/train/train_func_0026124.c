mock_certificate_finalize (GObject *obj)
{
	MockCertificate *self = MOCK_CERTIFICATE (obj);
	g_assert (self->created_on == g_thread_self ());
	g_free (self->data);
	G_OBJECT_CLASS (mock_certificate_parent_class)->finalize (obj);
}
