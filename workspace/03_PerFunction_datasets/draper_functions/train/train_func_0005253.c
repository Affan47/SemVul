ctx_set_transport_enabled(TCS_CONTEXT_HANDLE tcsContext, UINT32 hTransHandle)
{
	TSS_RESULT result = TSS_SUCCESS;
	struct tcs_context *tmp, *self = NULL;

	MUTEX_LOCK(tcs_ctx_lock);

	tmp = tcs_context_table;
	while (tmp) {
		if (tmp->handle == tcsContext) {
			self = tmp;
			break;
		}

		tmp = tmp->next;
	}

	if (self) {
		self->flags |= TSS_CONTEXT_FLAG_TRANSPORT_ENABLED;
		self->transHandle = hTransHandle;
	} else
		result = TCSERR(TCS_E_INVALID_CONTEXTHANDLE);

	MUTEX_UNLOCK(tcs_ctx_lock);

	return result;
}
