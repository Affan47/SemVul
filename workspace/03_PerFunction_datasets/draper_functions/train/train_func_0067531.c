character_data_handler(void *data, const XML_Char *chars, int len)
{
	Document *doc = (Document *)data;

	Node *nod = doc->root;

	for (int i = 1; i < doc->_depth; ++i)
	{
		nod = &(nod->children.back());
	}
	int x, y;

	x = 0;
	y = len-1;

	while (isspace(chars[y]) && y > 0) --y;
	while (isspace(chars[x]) && x < y) ++x;

	nod->cdata = std::string(chars, x, y+1);
}
