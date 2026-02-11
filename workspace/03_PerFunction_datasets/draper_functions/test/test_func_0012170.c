recv(void *data, int size, CL_IPAddress &from)
{
	char *_data = (char *) data;
	int total = 0;


	while (!impl->push_stack.empty())
	{
		std::string &str = impl->push_stack.top();
		if (str.size() < (unsigned int)size)
		{
			memcpy(_data, str.data(), str.size());
			_data += str.size();
			total += str.size();
			size -= str.size();
			impl->push_stack.pop();
		}
		else
		{
			memcpy(_data, str.data(), size);
			str = str.substr(size);
			total += size;
			return total;
		}
	}


	sockaddr_in addr_in;
	memset(&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;

	socklen_t addr_size = sizeof(addr_in);

	int result = ::recvfrom(
		impl->sock,
		_data,
		size,
		0,
		(sockaddr *) &addr_in,
		&addr_size);
	if (result < 0) throw CL_Error("CL_Socket::recv failed");
	total += result;

	if (impl->read) impl->read->start_listen();
	from = CL_Socket_Generic::create_ip_address(addr_in);
	return total;
}
