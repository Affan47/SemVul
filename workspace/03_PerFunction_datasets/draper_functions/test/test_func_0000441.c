git_reflog_free(git_reflog *reflog)
{
	unsigned int i;
	git_reflog_entry *entry;

	for (i=0; i < reflog->entries.length; i++) {
		entry = git_vector_get(&reflog->entries, i);

		git_signature_free(entry->committer);

		git__free(entry->msg);
		git__free(entry);
	}

	git_vector_free(&reflog->entries);
	git__free(reflog->ref_name);
	git__free(reflog);
}
