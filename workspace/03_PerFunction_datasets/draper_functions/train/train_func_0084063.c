readFromDevice(char* buffer, std::streamsize length)
{
	if (!_pIstr)
		return 0;

	int count = 0;

	while (!_eof)
	{
		int m = (static_cast<int>(length) - count)/2 - static_cast<int>(_pTransform->blockSize());


		if (m <= 0)
			break;

		int n = 0;

		if (_pIstr->good())
		{
			_pIstr->read(reinterpret_cast<char*>(_buffer.begin()), m);
			n = static_cast<int>(_pIstr->gcount());
		}

		if (n == 0)
		{
			_eof = true;


			count += static_cast<int>(_pTransform->finalize(
				reinterpret_cast<unsigned char*>(buffer + count),
				static_cast<int>(length) - count));
		}
		else
		{

			count += static_cast<int>(_pTransform->transform(
				_buffer.begin(),
				n,
				reinterpret_cast<unsigned char*>(buffer + count),
				static_cast<int>(length) - count));
		}
	}

	return count;
}
