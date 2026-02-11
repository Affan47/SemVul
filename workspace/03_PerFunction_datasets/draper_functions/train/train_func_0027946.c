destroy_client_lease (lease)
	struct client_lease *lease;
{
	if (lease -> server_name)
		dfree (lease -> server_name, MDL);
	if (lease -> filename)
		dfree (lease -> filename, MDL);
	option_state_dereference (&lease -> options, MDL);
	free_client_lease (lease, MDL);
}
