git_reflog_free(git_reflog *reflog)
{
	unsigned int i;
	git_reflog_entry *entry;

	for (i=0; i < reflog->entries.length; i++) {
		entry = git_vector_get(&reflog->entries, i);

		free(entry->oid_old);
		free(entry->oid_cur);

		git_signature_free(entry->committer);

		free(entry->msg);
		free(entry);
	}

	git_vector_free(&reflog->entries);
	free(reflog->ref_name);
	free(reflog);
}
