i40e_del_filter(struct i40e_vsi *vsi,
		     u8 *macaddr, s16 vlan,
		     bool is_vf, bool is_netdev)
{
	struct i40e_mac_filter *f;

	if (!vsi || !macaddr)
		return;

	f = i40e_find_filter(vsi, macaddr, vlan, is_vf, is_netdev);
	if (!f || f->counter == 0)
		return;

	if (is_vf) {
		if (f->is_vf) {
			f->is_vf = false;
			f->counter--;
		}
	} else if (is_netdev) {
		if (f->is_netdev) {
			f->is_netdev = false;
			f->counter--;
		}
	} else {

		int min_f = 0;

		min_f += (f->is_vf ? 1 : 0);
		min_f += (f->is_netdev ? 1 : 0);

		if (f->counter > min_f)
			f->counter--;
	}


	if (f->counter == 0) {
		f->changed = true;
		vsi->flags |= I40E_VSI_FLAG_FILTER_CHANGED;
		vsi->back->flags |= I40E_FLAG_FILTER_SYNC;
	}
}
