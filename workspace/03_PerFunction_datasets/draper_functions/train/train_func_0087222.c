vmci_doorbell_notify(struct vmci_handle dst, u32 priv_flags)
{
	int retval;
	enum vmci_route route;
	struct vmci_handle src;

	if (vmci_handle_is_invalid(dst) ||
	    (priv_flags & ~VMCI_PRIVILEGE_ALL_FLAGS))
		return VMCI_ERROR_INVALID_ARGS;

	src = VMCI_INVALID_HANDLE;
	retval = vmci_route(&src, &dst, false, &route);
	if (retval < VMCI_SUCCESS)
		return retval;

	if (VMCI_ROUTE_AS_HOST == route)
		return vmci_ctx_notify_dbell(VMCI_HOST_CONTEXT_ID,
					     dst, priv_flags);

	if (VMCI_ROUTE_AS_GUEST == route)
		return dbell_notify_as_guest(dst, priv_flags);

	pr_warn("Unknown route (%d) for doorbell\n", route);
	return VMCI_ERROR_DST_UNREACHABLE;
}
