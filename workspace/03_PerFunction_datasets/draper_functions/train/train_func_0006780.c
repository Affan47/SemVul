efx_siena_sriov_set_vf_vlan(struct efx_nic *efx, int vf_i,
				u16 vlan, u8 qos)
{
	struct siena_nic_data *nic_data = efx->nic_data;
	struct siena_vf *vf;
	u16 tci;

	if (vf_i >= efx->vf_init_count)
		return -EINVAL;
	vf = nic_data->vf + vf_i;

	mutex_lock(&vf->status_lock);
	tci = (vlan & VLAN_VID_MASK) | ((qos & 0x7) << VLAN_PRIO_SHIFT);
	vf->addr.tci = htons(tci);
	__efx_siena_sriov_update_vf_addr(vf);
	mutex_unlock(&vf->status_lock);

	return 0;
}
