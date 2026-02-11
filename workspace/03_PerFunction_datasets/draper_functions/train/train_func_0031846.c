BlitSources(int in_fd) {
	for (unsigned int x = 0; x < packetsource_vec.size(); x++) {
		kis_protocol_cache cache;

		if (in_fd == -1) {
			if (globalreg->kisnetserver->SendToAll(source_protoref,
												   (void *) packetsource_vec[x]) < 0)
				break;
		} else {
			if (globalreg->kisnetserver->SendToClient(in_fd, source_protoref,
													  (void *) packetsource_vec[x],
													  &cache) < 0)
				break;
		}
	}
}
