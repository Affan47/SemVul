matchacl(std::string localid, std::string remoteid, std::vector<struct aclelement> &acl)
{
	debugprint(localdebugmode, PLUGIN_SHORT_NAME ": Local: %s Remote: %s",
		localid.c_str(), remoteid.c_str());

	for (std::vector<struct aclelement>::iterator i = acl.begin();
		i != acl.end(); i++)
	{
		if (matchid(localid, (*i).localid) || (*i).localid == "all")
		{
			debugprint(localdebugmode, PLUGIN_SHORT_NAME ": Got Local match (%s)", (*i).localid.c_str());

			if (!(*i).remoteids.size())
			{
				debugprint(localdebugmode, PLUGIN_SHORT_NAME ": Remote acl empty; matching");
				return (*i).filtered;
			}
			for (std::vector<std::string>::iterator j = (*i).remoteids.begin();
				j != (*i).remoteids.end(); j++)
			{
				if ((*j) == "groupchat")
				{
					if (remoteid.find("groupchat-", 0) == 0)
					{
						debugprint(localdebugmode, PLUGIN_SHORT_NAME ": Got groupchat match (%s)", (*j).c_str());
						return (*i).filtered;
					}
				}
				if (matchid(remoteid, (*j)))
				{
					debugprint(localdebugmode, PLUGIN_SHORT_NAME ": Got Remote match (%s)", (*j).c_str());
					return (*i).filtered;
				}
			}

			continue;
		}
	}

	debugprint(localdebugmode, PLUGIN_SHORT_NAME ": No match");

	return false;
}
