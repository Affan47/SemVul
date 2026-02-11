server_check_hashes(IrmoServer *server,
                               unsigned int local_hash,
                               unsigned int server_hash)
{
	unsigned int local_hash_expected=0, server_hash_expected=0;


        if (server->client_interface != NULL) {
                local_hash_expected = irmo_interface_hash(server->client_interface);
        } else {
                local_hash_expected = 0;
        }

        if (server->world != NULL) {
                server_hash_expected = irmo_interface_hash(server->world->iface);
        } else {
                server_hash_expected = 0;
        }


        return local_hash == local_hash_expected
            && server_hash == server_hash_expected;
}
