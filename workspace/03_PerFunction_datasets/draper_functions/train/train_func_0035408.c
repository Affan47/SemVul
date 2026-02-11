aa_label_next_confined(struct aa_label *label, int i)
{
	AA_BUG(!label);
	AA_BUG(i < 0);

	for (; i < label->size; i++) {
		if (!profile_unconfined(label->vec[i]))
			return i;
	}

	return i;
}
