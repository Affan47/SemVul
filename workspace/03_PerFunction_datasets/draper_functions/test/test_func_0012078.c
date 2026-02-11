collection_backend_factory_get_hash_key (EBackendFactory *factory)
{
	ECollectionBackendFactoryClass *class;

	class = E_COLLECTION_BACKEND_FACTORY_GET_CLASS (factory);
	g_return_val_if_fail (class->factory_name != NULL, NULL);

	return class->factory_name;
}
