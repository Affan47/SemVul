cgroup_config_insert_into_namespace_table(char *name, char *nspath)
{
	if (namespace_table_index >= CG_CONTROLLER_MAX)
		return 0;

	pthread_rwlock_wrlock(&namespace_table_lock);

	strcpy(config_namespace_table[namespace_table_index].name, name);
	strcpy(config_namespace_table[namespace_table_index].mount.path,
			nspath);
	config_namespace_table[namespace_table_index].mount.next = NULL;
	namespace_table_index++;

	pthread_rwlock_unlock(&namespace_table_lock);
	free(name);
	free(nspath);
	return 1;
}
