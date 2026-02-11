sendMessage(const std::string& message, const std::string& arg1, const std::string& arg2)
{
	std::string line;
	line.reserve(message.length() + arg1.length() +arg2.length() + 4);
	line.append(message);
	line.append(" ");
	line.append(arg1);
	if (!arg2.empty())
	{
		line.append(" ");
		line.append(arg2);
	}
	line.append("\r\n");
	sendString(line);
}
