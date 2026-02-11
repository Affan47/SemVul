audit_filter_type(int type)
{
	struct audit_entry *e;
	int result = 0;

	rcu_read_lock();
	if (list_empty(&audit_filter_list[AUDIT_FILTER_TYPE]))
		goto unlock_and_return;

	list_for_each_entry_rcu(e, &audit_filter_list[AUDIT_FILTER_TYPE],
				list) {
		int i;
		for (i = 0; i < e->rule.field_count; i++) {
			struct audit_field *f = &e->rule.fields[i];
			if (f->type == AUDIT_MSGTYPE) {
				result = audit_comparator(type, f->op, f->val);
				if (!result)
					break;
			}
		}
		if (result)
			goto unlock_and_return;
	}
unlock_and_return:
	rcu_read_unlock();
	return result;
}
