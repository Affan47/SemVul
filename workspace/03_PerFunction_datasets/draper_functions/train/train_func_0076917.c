cm_writing_lock(struct cm_store_entry *entry)
{
	if ((writing_lock == entry) || (writing_lock == NULL)) {
		if (writing_lock == NULL) {
			cm_log(3, "%s('%s') taking writing lock\n",
			       entry->cm_busname, entry->cm_nickname);
			writing_lock = entry;
		} else {
			abort();
		}
		return TRUE;
	} else {
		return FALSE;
	}
}
