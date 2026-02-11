udp_thread()
{
	char *buffer = 0;

	try
	{
		CL_EventListener listener;


		listener.add_trigger(udp_sock.get_read_trigger());


		listener.add_trigger(&udp_wakeup_client_trigger);

		listener.add_trigger(&udp_shutdown_trigger);

		int msg_size = accept_udp_socket.get_max_msg_size();
		buffer = new char[msg_size];

		while (true)
		{
			listener.wait();
			if (udp_shutdown_trigger.get_flag()) break;

			if (udp_sock.get_read_trigger()->get_flag())
			{

				CL_IPAddress from;
				int bytes_available = udp_sock.recv(buffer, msg_size, from);

				dispatch_udp_messege_client(from, bytes_available, buffer);
			}


			if (udp_wakeup_client_trigger.get_flag())
			{
				IPMassagePair udp_message;

				while (!send_udp_client_queue.empty())
				{
					udp_message = send_udp_client_queue.front();

					udp_sock.send(udp_message.second.c_str(), udp_message.second.size(), udp_message.first);

					send_udp_client_queue.pop();
				}

				udp_wakeup_client_trigger.reset();
			}

		}

		accept_udp_socket = CL_Socket(CL_Socket::udp);
		accept_udp_socket.set_nodelay();
	}
	catch (CL_Error err)
	{
		CL_Log::log("debug", "Error %1", err.message);
	}

	delete[] buffer;
}
