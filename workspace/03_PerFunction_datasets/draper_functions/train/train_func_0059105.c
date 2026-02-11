genericProcessKeyword(size_t messageNumber,
				       generic::updateKeywordHelper &helper)
{
	if (messageNumber < index.size())
	{
		map<string, size_t>::iterator p=
			uidmap.find(index[messageNumber].uid);

		if (p != uidmap.end())
		{
			folderDirty=true;
			return helper
				.doUpdateKeyword(folderMessageIndex[p->second]
						 .tag.getKeywords(),
						 keywordHashtable);
		}
	}
	return true;
}
