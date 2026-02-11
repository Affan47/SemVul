service_ensure_for_flags_sync (SecretService *self,
                               SecretServiceFlags flags,
                               GCancellable *cancellable,
                               GError **error)
{
	if (flags & SECRET_SERVICE_OPEN_SESSION)
		if (!secret_service_ensure_session_sync (self, cancellable, error))
			return FALSE;

	if (flags & SECRET_SERVICE_LOAD_COLLECTIONS)
		if (!secret_service_load_collections_sync (self, cancellable, error))
			return FALSE;

	return TRUE;
}
