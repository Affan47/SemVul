incrementUsage(const CatItem& item)
{
	for (int i = 0; i < catList.size(); ++i)
	{
		if (item == catList[i])
		{

			if (catList[i].usage < 0)
				catList[i].usage = 1;
			else
				++catList[i].usage;
			break;
		}
	}
}
