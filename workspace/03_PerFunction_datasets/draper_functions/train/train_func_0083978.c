smk_access_entry(char *subject_label, char *object_label,
			struct list_head *rule_list)
{
	int may = -ENOENT;
	struct smack_rule *srp;

	list_for_each_entry_rcu(srp, rule_list, list) {
		if (srp->smk_object->smk_known == object_label &&
		    srp->smk_subject->smk_known == subject_label) {
			may = srp->smk_access;
			break;
		}
	}


	if ((may & MAY_WRITE) == MAY_WRITE)
		may |= MAY_LOCK;
	return may;
}
