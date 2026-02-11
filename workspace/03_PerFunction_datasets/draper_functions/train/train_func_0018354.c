collection_take_service (SecretCollection *self,
                         SecretService *service)
{
	if (service == NULL)
		return;

	g_return_if_fail (self->pv->service == NULL);

	self->pv->service = service;
	g_object_add_weak_pointer (G_OBJECT (self->pv->service),
	                           (gpointer *)&self->pv->service);


	g_object_unref (service);
}
