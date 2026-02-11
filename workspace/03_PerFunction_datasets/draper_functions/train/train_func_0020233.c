dg_dispatch_as_guest(struct vmci_datagram *dg)
{
	int retval;
	struct vmci_resource *resource;

	resource = vmci_resource_by_handle(dg->src,
					   VMCI_RESOURCE_TYPE_DATAGRAM);
	if (!resource)
		return VMCI_ERROR_NO_HANDLE;

	retval = vmci_send_datagram(dg);
	vmci_resource_put(resource);
	return retval;
}
