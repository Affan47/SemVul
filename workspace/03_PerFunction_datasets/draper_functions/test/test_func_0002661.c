nvkm_client_search(struct nvkm_client *client, u64 handle)
{
	struct rb_node *node = client->objroot.rb_node;
	while (node) {
		struct nvkm_object *object =
			container_of(node, typeof(*object), node);
		if (handle < object->object)
			node = node->rb_left;
		else
		if (handle > object->object)
			node = node->rb_right;
		else
			return object;
	}
	return NULL;
}
