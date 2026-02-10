processMessage(const std::string& messageText)
{
	Poco::Message message;
	_pParser->parse(messageText, message);
	log(message);
}
