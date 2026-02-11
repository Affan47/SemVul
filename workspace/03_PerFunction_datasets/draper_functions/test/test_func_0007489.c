send_bytes_message(int fd, unsigned char msg, int len, unsigned char *data)
{
	COMMAND_PACKET out;
	COMMAND_PACKET in;

	out.command = msg;
	out.data_length = (unsigned char) ((len > MAX_DATA_LENGTH) ? MAX_DATA_LENGTH : len);
	memcpy(out.data, data, out.data_length);


	send_packet(fd, &out, &in);
}
