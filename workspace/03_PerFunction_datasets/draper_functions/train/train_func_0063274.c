conn_get(struct user_conn_info *uci)
{
	unsigned int key;
	struct conn_info *ci;

	key = uci_generate_key(uci);
	hash_lock(&conn_table);
	if ((ci = hash_get(&conn_table, key, uci))) {
		pthread_mutex_lock(&ci->mutex);
		++ci->use_count;
		pthread_mutex_unlock(&ci->mutex);
	}
	hash_unlock(&conn_table);
	return ci;
}
