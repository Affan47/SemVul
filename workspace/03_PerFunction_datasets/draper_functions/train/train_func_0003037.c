vrrp_vmac_xmit_base_handler(vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	if (vrrp->vmac_flags & VRRP_VMAC_FL_SET)
		vrrp->vmac_flags |= VRRP_VMAC_FL_XMITBASE;
}
