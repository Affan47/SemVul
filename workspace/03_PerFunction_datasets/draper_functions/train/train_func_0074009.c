send_file_sig_packet(ushort sum_sig,int length_sig)
{
	ubyte data[MAX_PACKET_SIZE];
	int packet_size = 0;

	BUILD_HEADER(FILE_SIG_INFO);
	ADD_USHORT(sum_sig);
	ADD_INT(length_sig);

	multi_io_send_reliable(Net_player, data, packet_size);
}
