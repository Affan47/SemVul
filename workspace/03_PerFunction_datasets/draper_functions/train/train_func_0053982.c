overlay_removal_is_ok(struct of_overlay *ov)
{
	struct of_changeset_entry *ce;

	list_for_each_entry(ce, &ov->cset.entries, node) {
		if (!overlay_is_topmost(ov, ce->np)) {
			pr_err("%s: overlay #%d is not topmost\n",
					__func__, ov->id);
			return 0;
		}
	}

	return 1;
}
