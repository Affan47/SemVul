dependent_queue_recalc_main (GSList *work)
{


	while (work) {
		GnmDependent *dep = work->data;
		int const t = dependent_type (dep);
		GnmDependentClass *klass = g_ptr_array_index (dep_classes, t);


		work = g_slist_delete_link (work, work);

		if (klass->changed) {
			GSList *extra = klass->changed (dep);
			if (extra) {
				g_slist_last (extra)->next = work;
				work = extra;
			}
		}
	}
}
