resetList_impl(void)
{

	if (d_listItems.empty())
	{
		return false;
	}

	else
	{

		while (!d_listItems.empty())
		{
		    ItemEntry* item = d_listItems[0];
			d_pane->removeChildWindow(item);
			if (item->isDestroyedByParent())
			{
			    WindowManager::getSingleton().destroyWindow(item);
			}
		}


		return true;
	}
}
