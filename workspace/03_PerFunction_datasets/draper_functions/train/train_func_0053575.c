CommandAllThreads(Data &cmd)
{
	JDWMessage msg(acceptfd);


	JVMThreadsList list;
	jvmdebug->GetThreadsList(list);
	dout(list);


	Data response;

	size_t offset = JDWP_PACKET_HEADER_SIZE + JDWP_RESPONSE_HEADER_SIZE;


	AddJDWInt(response, offset, be_htobl(list.size()));


	JVMThreadsList::const_iterator b = list.begin();
	for( ; b != list.end(); b++ ) {
		const JVMThreadsEntry &entry = *b;

		AddJDWInt(response, offset, be_htobl(entry.Id));
	}

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
