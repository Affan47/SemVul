free_pasid_states_level2(struct pasid_state **tbl)
{
	struct pasid_state **ptr;
	int i;

	for (i = 0; i < 512; ++i) {
		if (tbl[i] == NULL)
			continue;

		ptr = (struct pasid_state **)tbl[i];
		free_pasid_states_level1(ptr);
	}
}
