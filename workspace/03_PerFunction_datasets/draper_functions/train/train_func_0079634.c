cb_single_contained_collect (DependencySingle const *depsingle,
			     G_GNUC_UNUSED gpointer ignored,
			     CollectClosure *user)
{
	if (range_contains (user->target, depsingle->pos.col, depsingle->pos.row))
		micro_hash_foreach_dep (depsingle->deps, dep, {
			if (!(dep->flags & (DEPENDENT_FLAGGED | DEPENDENT_CAN_RELOCATE)) &&
			    dependent_type (dep) != DEPENDENT_DYNAMIC_DEP) {
				dep->flags |= DEPENDENT_FLAGGED;
				user->list = g_slist_prepend (user->list, dep);
			}});
}
