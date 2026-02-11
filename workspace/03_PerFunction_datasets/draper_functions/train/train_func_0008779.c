aa_label_init(struct aa_label *label, int size)
{
	AA_BUG(!label);
	AA_BUG(size < 1);

	label->sid = aa_alloc_sid();
	if (label->sid == AA_SID_INVALID)
		return false;

	label->size = size;
	label->vec[size] = NULL;
	kref_init(&label->count);
	RB_CLEAR_NODE(&label->node);

	return true;
}
