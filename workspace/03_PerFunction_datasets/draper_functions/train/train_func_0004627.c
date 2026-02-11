vmci_ctx_qp_exists(struct vmci_ctx *context, struct vmci_handle handle)
{
	if (context == NULL || vmci_handle_is_invalid(handle))
		return false;

	return vmci_handle_arr_has_entry(context->queue_pair_array, handle);
}
