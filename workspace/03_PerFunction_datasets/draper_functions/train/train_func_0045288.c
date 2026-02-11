irmo_method_atom_verify(IrmoPacket *packet, IrmoClient *client)
{
	IrmoMethod *method;
        IrmoServer *server;
	unsigned int i;

        server = client->server;

	if (server->world == NULL) {
		return 0;
        }


	if (!irmo_packet_readi8(packet, &i)) {
		return 0;
        }


	if (i >= client->server->world->iface->nmethods) {
		return 0;
        }

	method = client->server->world->iface->methods[i];


	for (i=0; i<method->narguments; ++i) {
		if (!irmo_packet_verify_value
			(packet, method->arguments[i]->type)) {
			return 0;
                }
	}

	return 1;
}
