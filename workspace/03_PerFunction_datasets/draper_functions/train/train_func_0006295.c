ib_ucontext_notifier_end_account(struct ib_ucontext *context)
{
	int zero_notifiers = atomic_dec_and_test(&context->notifier_count);

	if (zero_notifiers &&
	    !list_empty(&context->no_private_counters)) {


		struct ib_umem_odp *odp_data, *next;


		down_write(&context->umem_rwsem);


		if (!atomic_read(&context->notifier_count)) {
			list_for_each_entry_safe(odp_data, next,
						 &context->no_private_counters,
						 no_private_counters) {
				mutex_lock(&odp_data->umem_mutex);
				odp_data->mn_counters_active = true;
				list_del(&odp_data->no_private_counters);
				complete_all(&odp_data->notifier_completion);
				mutex_unlock(&odp_data->umem_mutex);
			}
		}

		up_write(&context->umem_rwsem);
	}
}
