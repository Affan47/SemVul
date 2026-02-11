is_sadump_xen(void)
{
	if (xen_kdump_data.p2m_mfn) {
		if (!XEN_CORE_DUMPFILE()) {
			pc->flags |= XEN_CORE;
			nd->xen_kdump_data = &xen_kdump_data;
			nd->xen_kdump_data->last_mfn_read = UNINITIALIZED;
			nd->xen_kdump_data->last_pmd_read = UNINITIALIZED;
			nd->xen_kdump_data->flags |= KDUMP_MFN_LIST;
		}
		return TRUE;
	}

	return FALSE;
}
