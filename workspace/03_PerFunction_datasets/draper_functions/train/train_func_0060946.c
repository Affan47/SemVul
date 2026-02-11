setremoteid(std::string id)
{

	std::string idcopy = id;

	size_t n = idcopy.find_last_of(";");

	if (n != std::string::npos)
		idcopy = idcopy.substr(0, n);


	if (idcopy == remoteid) return;


	if (idcopy == localid) return;

	if (!gotremoteid)
	{
		remoteid = idcopy;
		gotremoteid = true;
	}
	else if (!groupchat)
	{
		remoteid = "groupchat-" + stringprintf("%d", (int) time(NULL));
		debugprint(localdebugmode, PROTOCOL_NAME ": Group chat, %s\n", remoteid.c_str());
		groupchat = true;
	}
}
