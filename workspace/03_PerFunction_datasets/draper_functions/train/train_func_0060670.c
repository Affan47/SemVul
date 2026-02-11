wsp_cap_duplicate(Capability *cap) {
	Capability *new_cap;

	if (!cap)
		return NULL;

	new_cap = wsp_cap_create(cap->id,
				octstr_duplicate(cap->name),
				octstr_duplicate(cap->data));
	new_cap->accept = cap->accept;
	return new_cap;
}
