item(int depth, GlyphIndex t) {
    if (t < 0 || t >= items_.used_) {
	ListImpl_range_error(t);
    }
    GlyphIndex target = items_.used_ - 1 - t;
    HitTargetList& list = items_.lists_[target];
    if (depth >= list.avail_) {
	int new_avail = depth + HitTargetList_fixed;
	HitTarget* new_targets = new HitTarget[new_avail];
	Memory::copy(
	    list.targets_, new_targets, (list.used_ + 1) * sizeof(HitTarget)
	);
	if (list.targets_ != list.fixed_targets_) {
	    delete list.targets_;
	}
	HitTarget* i;
	for (i = &new_targets[list.avail_]; i < &new_targets[new_avail]; i++) {
	    i->glyph_ = nil;
	}
	list.avail_ = new_avail;
	list.targets_ = new_targets;
    }
    if (depth > list.used_) {
	list.used_ = depth;
    }
    return list.targets_[depth];
}
