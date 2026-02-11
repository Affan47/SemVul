nvme_find_ns(struct nvme_ctrl *ctrl, unsigned nsid)
{
	struct nvme_ns *ns;

	lockdep_assert_held(&ctrl->namespaces_mutex);

	list_for_each_entry(ns, &ctrl->namespaces, list) {
		if (ns->ns_id == nsid)
			return ns;
		if (ns->ns_id > nsid)
			break;
	}
	return NULL;
}
