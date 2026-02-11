addThisClient(Client *c)
{
	if(c)
	{
		BaseMenuItem *item = new BaseMenuItem();

		item->client = c;

		if(c->getClientIconName() == NULL)
		{
			item->name = "untitled";
		}else
		{
			item->name = c->getClientIconName();
		}

		item->function=SHOW;

		insert(item);
	}
}
