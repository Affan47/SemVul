usnic_vnic_get_resources(struct usnic_vnic *vnic, enum usnic_vnic_res_type type,
				int cnt, void *owner)
{
	struct usnic_vnic_res_chunk *src, *ret;
	struct usnic_vnic_res *res;
	int i;

	if (usnic_vnic_res_free_cnt(vnic, type) < cnt || cnt < 1 || !owner)
		return ERR_PTR(-EINVAL);

	ret = kzalloc(sizeof(*ret), GFP_ATOMIC);
	if (!ret) {
		usnic_err("Failed to allocate chunk for %s - Out of memory\n",
				usnic_vnic_pci_name(vnic));
		return ERR_PTR(-ENOMEM);
	}

	ret->res = kzalloc(sizeof(*(ret->res))*cnt, GFP_ATOMIC);
	if (!ret->res) {
		usnic_err("Failed to allocate resources for %s. Out of memory\n",
				usnic_vnic_pci_name(vnic));
		kfree(ret);
		return ERR_PTR(-ENOMEM);
	}

	spin_lock(&vnic->res_lock);
	src = &vnic->chunks[type];
	for (i = 0; i < src->cnt && ret->cnt < cnt; i++) {
		res = src->res[i];
		if (!res->owner) {
			src->free_cnt--;
			res->owner = owner;
			ret->res[ret->cnt++] = res;
		}
	}

	spin_unlock(&vnic->res_lock);
	ret->type = type;
	ret->vnic = vnic;
	WARN_ON(ret->cnt != cnt);

	return ret;
}
