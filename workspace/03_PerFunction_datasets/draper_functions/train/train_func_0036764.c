CommandSuspend(Data &cmd)
{
	JDWMessage msg(acceptfd);


	jvmdebug->Stop();


	MAKE_JDWPPACKET(rpack, cmd);

	size_t size;

	Barry::Protocol::JDWP::Packet packet;

	size = JDWP_PACKET_HEADER_SIZE + JDWP_RESPONSE_HEADER_SIZE;

	packet.length = be_htobl(size);
	packet.id = rpack->id;
	packet.flags = 0x80;
	packet.u.response.errorcode = be_htobs(0);

	Data response(&packet, size);

	msg.Send(response);
}
