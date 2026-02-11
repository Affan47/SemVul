set_mtrr_var_ranges(unsigned int index, struct mtrr_var_range *vr)
{
	unsigned int lo, hi;
	bool changed = false;

	rdmsr(MTRRphysBase_MSR(index), lo, hi);
	if ((vr->base_lo & 0xfffff0ffUL) != (lo & 0xfffff0ffUL)
	    || (vr->base_hi & (size_and_mask >> (32 - PAGE_SHIFT))) !=
		(hi & (size_and_mask >> (32 - PAGE_SHIFT)))) {

		mtrr_wrmsr(MTRRphysBase_MSR(index), vr->base_lo, vr->base_hi);
		changed = true;
	}

	rdmsr(MTRRphysMask_MSR(index), lo, hi);

	if ((vr->mask_lo & 0xfffff800UL) != (lo & 0xfffff800UL)
	    || (vr->mask_hi & (size_and_mask >> (32 - PAGE_SHIFT))) !=
		(hi & (size_and_mask >> (32 - PAGE_SHIFT)))) {
		mtrr_wrmsr(MTRRphysMask_MSR(index), vr->mask_lo, vr->mask_hi);
		changed = true;
	}
	return changed;
}
