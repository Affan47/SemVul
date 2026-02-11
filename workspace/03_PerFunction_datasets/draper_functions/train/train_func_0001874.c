smk_find_entry(const char *string)
{
	unsigned int hash;
	struct hlist_head *head;
	struct smack_known *skp;

	hash = full_name_hash(string, strlen(string));
	head = &smack_known_hash[hash & (SMACK_HASH_SLOTS - 1)];

	hlist_for_each_entry_rcu(skp, head, smk_hashed)
		if (strcmp(skp->smk_known, string) == 0)
			return skp;

	return NULL;
}
