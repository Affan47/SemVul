haveHost(const StreamHostList &list, const Jid &j)
{
	for(StreamHostList::ConstIterator it = list.begin(); it != list.end(); ++it) {
		if((*it).jid().compare(j))
			return true;
	}
	return false;
}
