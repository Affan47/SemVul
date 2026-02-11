addChild_impl(Window* wnd)
{

    if (wnd->testClassName("ItemEntry"))
    {

        if (d_pane != this)
        {
            d_pane->addChildWindow(wnd);
        }

        else
        {
            Window::addChild_impl(wnd);
        }

        ItemEntry* item = static_cast<ItemEntry*>(wnd);
	    if (item->d_ownerList != this)
	    {


            if (d_sortEnabled)
            {
                d_listItems.insert(
                    std::upper_bound(d_listItems.begin(), d_listItems.end(), item, getRealSortCallback()),
                    item);
            }

            else
            {
                d_listItems.push_back(item);
            }
	        item->d_ownerList = this;
		    handleUpdatedItemData();
	    }
	}

    else
    {
        Window::addChild_impl(wnd);
    }
}
