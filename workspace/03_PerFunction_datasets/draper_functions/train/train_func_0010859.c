getCategoryCount()
{
  int i = 0;

	for(xmlNode* category = get_first_category();
		category != NULL;
		category = get_next_category(category))
	{
      i++;
	}

  return i;
}
