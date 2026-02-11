AutoDetectInputStream(std::istream& istr, const std::string& pre, const std::string& post, bool reposition, Poco::UInt32 start):
	AutoDetectIOS(istr, pre, post, reposition, start),
	std::istream(&_buf)
{
}
