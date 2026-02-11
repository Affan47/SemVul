decompress_gz_file(const std::string &file_path, vector_byte & buffer)
{
	CFileGZInputStream	iss(file_path);
	if (!iss.fileOpenCorrectly())
		return false;

	buffer.clear();

	const int bytes2read = 1 << 20;
	int	act_read;
	size_t	total_bytes = 0;

	buffer.reserve( iss.getTotalBytesCount() );

	do
	{
		buffer.resize( 1000+bytes2read + buffer.size() );
		act_read = iss.ReadBuffer( &buffer[total_bytes], bytes2read );
		total_bytes += act_read;
	} while (act_read==bytes2read);

	buffer.resize( total_bytes );
	return true;
}
