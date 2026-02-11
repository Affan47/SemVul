beginList(const std::string& path, bool extended)
{
	delete _pDataStream;
	_pDataStream = 0;
	_pDataStream = new SocketStream(establishDataConnection(extended ? "LIST" : "NLST", path));
	return *_pDataStream;
}
