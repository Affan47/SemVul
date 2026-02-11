received_udp_packet(CL_NetPacket &packet)
{
	try
	{
		unsigned char command = packet.input.read_uchar8();
		switch (command)
		{
		case cmd_udp_connect:
			{


				CL_OutputSource_Memory cmd;
				cmd.write_uchar8(cmd_udp_connect);

				CL_MutexSection mutex_section(&mutex);
				bool tcp_queue_empty = send_tcp_queue.empty();
				send_tcp_queue.push(cmd.get_data());
				if (tcp_queue_empty) wakeup_trigger.set_flag();

				udp_available = true;
			}
			break;

		case cmd_netpacket_msg:
			{
				std::map<int, std::string>::iterator iter = remote_atoms.find(packet.input.read_ushort16());


				if (iter == remote_atoms.end()) break;

				std::string channel_name = (*iter).second;

				int pos = packet.input.tell();
				CL_NetPacket message(packet.get_data()+pos, packet.get_size()-pos);
				CL_MutexSection mutex_section(&netsession->mutex);
				netsession->received_netpacket(channel_name, message, this);
			}
			break;
		}
	}
	catch (CL_Error error)
	{

	}
}
