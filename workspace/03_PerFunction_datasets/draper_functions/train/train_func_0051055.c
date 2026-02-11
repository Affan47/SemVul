cgroup_print_rules_config(FILE *fp)
{

	struct cgroup_rule *itr = NULL;


	int i = 0;

	pthread_rwlock_rdlock(&rl_lock);

	if (!(rl.head)) {
		fprintf(fp, "The rules table is empty.\n\n");
		pthread_rwlock_unlock(&rl_lock);
		return;
	}

	itr = rl.head;
	while (itr) {
		fprintf(fp, "Rule: %s", itr->username);
		if (itr->procname)
			fprintf(fp, ":%s", itr->procname);
		fprintf(fp, "\n");

		if (itr->uid == CGRULE_WILD)
			fprintf(fp, "  UID: any\n");
		else if (itr->uid == CGRULE_INVALID)
			fprintf(fp, "  UID: N/A\n");
		else
			fprintf(fp, "  UID: %d\n", itr->uid);

		if (itr->gid == CGRULE_WILD)
			fprintf(fp, "  GID: any\n");
		else if (itr->gid == CGRULE_INVALID)
			fprintf(fp, "  GID: N/A\n");
		else
			fprintf(fp, "  GID: %d\n", itr->gid);

		fprintf(fp, "  DEST: %s\n", itr->destination);

		fprintf(fp, "  CONTROLLERS:\n");
		for (i = 0; i < MAX_MNT_ELEMENTS; i++) {
			if (itr->controllers[i])
				fprintf(fp, "    %s\n", itr->controllers[i]);
		}
		fprintf(fp, "\n");
		itr = itr->next;
	}
	pthread_rwlock_unlock(&rl_lock);
}
