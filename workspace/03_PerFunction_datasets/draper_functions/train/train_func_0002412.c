dumpTagMap()
{
	for( TagMap::iterator iter = tagMap.begin(); iter != tagMap.end(); iter++ )
	{
		Node* pNode=((*iter).second);
		if (!pNode->children.size())
			Log::info( "%s%s%s%s",
					pNode->key.c_str(),
					pNode->value.size()?" = '":"",
					pNode->value.c_str(),
					pNode->value.size()?"'":""
				);
	}
}
