fini ( void )
{
	slurm_mutex_lock(&as_mysql_cluster_list_lock);
	if (as_mysql_cluster_list) {
		list_destroy(as_mysql_cluster_list);
		as_mysql_cluster_list = NULL;
	}
	if (as_mysql_total_cluster_list) {
		list_destroy(as_mysql_total_cluster_list);
		as_mysql_total_cluster_list = NULL;
	}
	slurm_mutex_unlock(&as_mysql_cluster_list_lock);
	slurm_mutex_destroy(&as_mysql_cluster_list_lock);
	destroy_mysql_db_info(mysql_db_info);
	xfree(mysql_db_name);
	xfree(default_qos_str);
	mysql_db_cleanup();
	return SLURM_SUCCESS;
}
