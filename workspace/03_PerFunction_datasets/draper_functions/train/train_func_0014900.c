begin_lock_file (GkmGnome2Storage *self, GkmTransaction *transaction)
{
	dotlock_t lockh;


	g_assert (GKM_IS_GNOME2_STORAGE (self));
	g_assert (GKM_IS_TRANSACTION (transaction));

	g_return_val_if_fail (!gkm_transaction_get_failed (transaction), -1);
	gkm_debug ("modifying: %s", self->filename);

	lockh = lock_and_open_file (self->filename, O_RDONLY | O_CREAT);
	if (!lockh) {
		gkm_transaction_fail (transaction, CKR_FUNCTION_FAILED);
		return -1;
	}

	;
	gkm_transaction_add (transaction, self, complete_lock_file, lockh);
	return dotlock_get_fd (lockh);
}
