git_hashtable_merge(git_hashtable *self, git_hashtable *other)
{
	if (resize_to(self, (self->size + other->size) * 2) < GIT_SUCCESS)
		return GIT_ENOMEM;

	return insert_nodes(self, other->nodes, other->key_count);
}
