enqueueMessage(const std::string& messageText, const Poco::Net::SocketAddress& senderAddress)
{
	_queue.enqueueNotification(new MessageNotification(messageText, senderAddress));
}
