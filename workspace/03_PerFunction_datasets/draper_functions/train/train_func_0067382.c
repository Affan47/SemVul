analyze_live_sets(struct compilation_unit *cu)
{
	struct bitset *old_live_out_set = NULL;
	struct bitset *old_live_in_set = NULL;
	struct basic_block *this;
	bool changed;
	int err = 0;

	old_live_in_set = alloc_bitset(cu->nr_vregs);
	if (!old_live_in_set) {
		err = -ENOMEM;
		goto out;
	}

	old_live_out_set = alloc_bitset(cu->nr_vregs);
	if (!old_live_out_set) {
		err = -ENOMEM;
		goto out;
	}


	do {
		changed = false;

		for_each_basic_block_reverse(this, &cu->bb_list) {
			struct basic_block *succ;
			unsigned long i;

			bitset_copy_to(this->live_in_set, old_live_in_set);
			bitset_copy_to(this->live_out_set, old_live_out_set);

			bitset_copy_to(this->live_out_set, this->live_in_set);
			bitset_sub(this->def_set, this->live_in_set);
			bitset_union_to(this->use_set, this->live_in_set);

			bitset_clear_all(this->live_out_set);
			for (i = 0; i < this->nr_successors; i++) {
				succ = this->successors[i];
				bitset_union_to(succ->live_in_set, this->live_out_set);
			}


			if (!bitset_equal(this->live_in_set, old_live_in_set) ||
			    !bitset_equal(this->live_out_set, old_live_out_set))
				changed = true;
		}
	} while (changed);
  out:
	free(old_live_out_set);
	free(old_live_in_set);
	return err;
}
