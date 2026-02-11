i40evf_del_vlans(struct i40evf_adapter *adapter)
{
	struct i40e_virtchnl_vlan_filter_list *vvfl;
	struct i40evf_vlan_filter *f, *ftmp;
	int len, i = 0, count = 0;
	bool more = false;

	if (adapter->current_op != I40E_VIRTCHNL_OP_UNKNOWN) {

		dev_err(&adapter->pdev->dev, "Cannot remove VLANs, command %d pending\n",
			adapter->current_op);
		return;
	}

	list_for_each_entry(f, &adapter->vlan_filter_list, list) {
		if (f->remove)
			count++;
	}
	if (!count) {
		adapter->aq_required &= ~I40EVF_FLAG_AQ_DEL_VLAN_FILTER;
		return;
	}
	adapter->current_op = I40E_VIRTCHNL_OP_DEL_VLAN;

	len = sizeof(struct i40e_virtchnl_vlan_filter_list) +
	      (count * sizeof(u16));
	if (len > I40EVF_MAX_AQ_BUF_SIZE) {
		dev_warn(&adapter->pdev->dev, "Too many delete VLAN changes in one request\n");
		count = (I40EVF_MAX_AQ_BUF_SIZE -
			 sizeof(struct i40e_virtchnl_vlan_filter_list)) /
			sizeof(u16);
		len = sizeof(struct i40e_virtchnl_vlan_filter_list) +
		      (count * sizeof(u16));
		more = true;
	}
	vvfl = kzalloc(len, GFP_KERNEL);
	if (!vvfl)
		return;

	vvfl->vsi_id = adapter->vsi_res->vsi_id;
	vvfl->num_elements = count;
	list_for_each_entry_safe(f, ftmp, &adapter->vlan_filter_list, list) {
		if (f->remove) {
			vvfl->vlan_id[i] = f->vlan;
			i++;
			list_del(&f->list);
			kfree(f);
		}
	}
	if (!more)
		adapter->aq_required &= ~I40EVF_FLAG_AQ_DEL_VLAN_FILTER;
	i40evf_send_pf_msg(adapter, I40E_VIRTCHNL_OP_DEL_VLAN, (u8 *)vvfl, len);
	kfree(vvfl);
}
