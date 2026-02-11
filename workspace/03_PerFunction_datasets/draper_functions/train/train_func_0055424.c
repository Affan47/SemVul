learn_pass2(FILE *stream)
{
	struct gr_learn_role_entry *tmp;
	struct gr_learn_file_node *subjects;

	learn_pass2in = stream;
	learn_pass2parse();

	merge_acl_rules();

	if (default_role_entry) {
		subjects = default_role_entry->subject_list;
		traverse_file_tree(subjects, &full_reduce_object_node, NULL, NULL);
		traverse_file_tree(subjects, &full_reduce_ip_node, NULL, NULL);
		traverse_file_tree(subjects, &ensure_subject_security, NULL, NULL);
	}

	for_each_list_entry(tmp, group_role_list) {
		subjects = tmp->subject_list;
		traverse_file_tree(subjects, &full_reduce_object_node, NULL, NULL);
		traverse_file_tree(subjects, &full_reduce_ip_node, NULL, NULL);
		traverse_file_tree(subjects, &ensure_subject_security, NULL, NULL);
	}

	for_each_list_entry(tmp, user_role_list) {
		subjects = tmp->subject_list;
		traverse_file_tree(subjects, &full_reduce_object_node, NULL, NULL);
		traverse_file_tree(subjects, &full_reduce_ip_node, NULL, NULL);
		traverse_file_tree(subjects, &ensure_subject_security, NULL, NULL);
	}

	for_each_list_entry(tmp, special_role_list) {
		subjects = tmp->subject_list;
		traverse_file_tree(subjects, &full_reduce_object_node, NULL, NULL);
		traverse_file_tree(subjects, &full_reduce_ip_node, NULL, NULL);
		traverse_file_tree(subjects, &ensure_subject_security, NULL, NULL);
	}

	return;
}
