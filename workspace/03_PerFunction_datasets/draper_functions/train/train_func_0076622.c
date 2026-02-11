vmci_datagram_get_priv_flags(u32 context_id,
					struct vmci_handle handle,
					u32 *priv_flags)
{
	if (context_id == VMCI_INVALID_ID)
		return VMCI_ERROR_INVALID_ARGS;

	if (context_id == VMCI_HOST_CONTEXT_ID) {
		struct datagram_entry *src_entry;
		struct vmci_resource *resource;

		resource = vmci_resource_by_handle(handle,
						   VMCI_RESOURCE_TYPE_DATAGRAM);
		if (!resource)
			return VMCI_ERROR_INVALID_ARGS;

		src_entry = container_of(resource, struct datagram_entry,
					 resource);
		*priv_flags = src_entry->priv_flags;
		vmci_resource_put(resource);
	} else if (context_id == VMCI_HYPERVISOR_CONTEXT_ID)
		*priv_flags = VMCI_MAX_PRIVILEGE_FLAGS;
	else
		*priv_flags = vmci_context_get_priv_flags(context_id);

	return VMCI_SUCCESS;
}
