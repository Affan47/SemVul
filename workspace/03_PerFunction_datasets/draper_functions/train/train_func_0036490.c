proto_reg_handoff_tetra(void)
{
	static gboolean initialized=FALSE;

	if (!initialized) {
		data_handle = find_dissector("data");
		tetra_handle = create_dissector_handle(dissect_tetra, proto_tetra);
		dissector_add_uint("udp.port", global_tetra_port, tetra_handle);
	}

}
