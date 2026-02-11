add_tuple(gpointer key_, gpointer value_, gpointer user_data)
{
	HV *hash = user_data;
	char *key = key_;
	char *value = value_;
	hv_store(hash, key, strlen(key), new_pv(value), 0);
}
