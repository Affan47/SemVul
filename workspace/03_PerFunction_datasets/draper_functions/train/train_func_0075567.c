MatchUpItem(char *text, int loc)
{
	char *word=MapSynonym(text);
	int ct=0;

	if(word==NULL)
		word=text;

	while(ct<=GameHeader.NumItems)
	{
		if(Items[ct].AutoGet && Items[ct].Location==loc &&
			xstrncasecmp(Items[ct].AutoGet,word,GameHeader.WordLength)==0)
			return(ct);
		ct++;
	}
	return(-1);
}
