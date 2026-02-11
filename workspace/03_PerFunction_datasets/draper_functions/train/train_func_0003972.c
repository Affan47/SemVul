CommandVersion(Data &cmd)
{
	JDWMessage msg(acceptfd);


	Data response;

	size_t offset = JDWP_PACKET_HEADER_SIZE + JDWP_RESPONSE_HEADER_SIZE;

	AddJDWString(response, offset, string("RIM JVM"));
	AddJDWInt(response, offset, be_htobl(1));
	AddJDWInt(response, offset, be_htobl(4));
	AddJDWString(response, offset, string("1.4"));
	AddJDWString(response, offset, string("RIM JVM"));

	response.ReleaseBuffer(offset);


	size_t total_size = response.GetSize();


	MAKE_JDWPPACKETPTR_BUF(cpack, response.GetBuffer(total_size));
	Barry::Protocol::JDWP::Packet &packet = *cpack;


	MAKE_JDWPPACKET(rpack, cmd);

	packet.length = be_htobl(total_size);
	packet.id = rpack->id;
	packet.flags = 0x80;
	packet.u.response.errorcode = be_htobs(0);

	response.ReleaseBuffer(total_size);
	msg.Send(response);
}
