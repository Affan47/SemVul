ntfs_get_size_for_mapping_pairs(const ntfs_volume *vol,
		const runlist_element *rl, const VCN first_vcn,
		const VCN last_vcn)
{
	LCN prev_lcn;
	int rls;
	bool the_end = false;

	BUG_ON(first_vcn < 0);
	BUG_ON(last_vcn < -1);
	BUG_ON(last_vcn >= 0 && first_vcn > last_vcn);
	if (!rl) {
		BUG_ON(first_vcn);
		BUG_ON(last_vcn > 0);
		return 1;
	}

	while (rl->length && first_vcn >= rl[1].vcn)
		rl++;
	if (unlikely((!rl->length && first_vcn > rl->vcn) ||
			first_vcn < rl->vcn))
		return -EINVAL;
	prev_lcn = 0;

	rls = 1;

	if (first_vcn > rl->vcn) {
		s64 delta, length = rl->length;


		if (unlikely(length < 0 || rl->lcn < LCN_HOLE))
			goto err_out;


		if (unlikely(last_vcn >= 0 && rl[1].vcn > last_vcn)) {
			s64 s1 = last_vcn + 1;
			if (unlikely(rl[1].vcn > s1))
				length = s1 - rl->vcn;
			the_end = true;
		}
		delta = first_vcn - rl->vcn;

		rls += 1 + ntfs_get_nr_significant_bytes(length - delta);


		if (likely(rl->lcn >= 0 || vol->major_ver < 3)) {
			prev_lcn = rl->lcn;
			if (likely(rl->lcn >= 0))
				prev_lcn += delta;

			rls += ntfs_get_nr_significant_bytes(prev_lcn);
		}

		rl++;
	}

	for (; rl->length && !the_end; rl++) {
		s64 length = rl->length;

		if (unlikely(length < 0 || rl->lcn < LCN_HOLE))
			goto err_out;


		if (unlikely(last_vcn >= 0 && rl[1].vcn > last_vcn)) {
			s64 s1 = last_vcn + 1;
			if (unlikely(rl[1].vcn > s1))
				length = s1 - rl->vcn;
			the_end = true;
		}

		rls += 1 + ntfs_get_nr_significant_bytes(length);


		if (likely(rl->lcn >= 0 || vol->major_ver < 3)) {

			rls += ntfs_get_nr_significant_bytes(rl->lcn -
					prev_lcn);
			prev_lcn = rl->lcn;
		}
	}
	return rls;
err_out:
	if (rl->lcn == LCN_RL_NOT_MAPPED)
		rls = -EINVAL;
	else
		rls = -EIO;
	return rls;
}
