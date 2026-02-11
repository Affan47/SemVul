agp_create_client(pid_t id)
{
	struct agp_client *new_client;

	new_client = kzalloc(sizeof(struct agp_client), GFP_KERNEL);
	if (new_client == NULL)
		return NULL;

	new_client->pid = id;
	agp_insert_client(new_client);
	return new_client;
}
