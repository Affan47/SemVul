recv(void *data, int size)
{
	char *_data = (char *) data;
	int received = 0;
	while (true)
	{
		impl->read_trigger.wait();

		CL_MutexSection mutex_section(&impl->mutex);
		while (!impl->receive_queue.empty())
		{
			std::string &chunk = impl->receive_queue.front();
			std::string::size_type copy_size = cl_min(static_cast<unsigned int>(size-received), chunk.length());

			memcpy(_data + received, chunk.data(), copy_size);
			received += copy_size;

			if (copy_size == chunk.length()) impl->receive_queue.pop();
			else chunk = chunk.substr(copy_size);

			if (received == size) return received;
		}
		if (impl->closed) return received;
		impl->read_trigger.reset();
	}

	return received;
}
