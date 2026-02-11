vmci_ctx_qp_create(struct vmci_ctx *context, struct vmci_handle handle)
{
	int result;

	if (context == NULL || vmci_handle_is_invalid(handle))
		return VMCI_ERROR_INVALID_ARGS;

	if (!vmci_handle_arr_has_entry(context->queue_pair_array, handle)) {
		vmci_handle_arr_append_entry(&context->queue_pair_array,
					     handle);
		result = VMCI_SUCCESS;
	} else {
		result = VMCI_ERROR_DUPLICATE_ENTRY;
	}

	return result;
}
