big_key_destroy(struct key *key)
{
	size_t datalen = (size_t)key->payload.data[big_key_len];

	if (datalen) {
		struct path *path = (struct path *)&key->payload.data[big_key_path];
		path_put(path);
		path->mnt = NULL;
		path->dentry = NULL;
	} else {
		kfree(key->payload.data[big_key_data]);
		key->payload.data[big_key_data] = NULL;
	}
}
