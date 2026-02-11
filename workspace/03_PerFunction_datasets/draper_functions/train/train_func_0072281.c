RemoveRoute(const std::string &inChannel, BufferedTransformation &destination, const std::string &outChannel)
{
	typedef ChannelSwitch::RouteMap::iterator MapIterator;
	pair<MapIterator, MapIterator> range = m_routeMap.equal_range(inChannel);

	for (MapIterator it = range.first; it != range.second; ++it)
		if (it->second.first == &destination && it->second.second == outChannel)
		{
			m_routeMap.erase(it);
			break;
		}
}
