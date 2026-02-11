removeItem( QString DataType )
	{

		if ( DataType == "Input" )
			{
				CurrentItems = InputItems;
				CurrentList = InputList;
			}
		if ( DataType == "Output" )
			{
				CurrentItems = OutputItems;
				CurrentList = OutputList;
			}
		if ( DataType == "Filter" )
			{
				CurrentItems = FilterItems;
				CurrentList = FilterList;
			}

		ActiveItem = CurrentList->currentItem();
		for (int i = 0; i < CurrentItems->count(); i++ )
			{
				if ( CurrentItems->at( i )->tellListViewItem() == ActiveItem )
					{
						delete CurrentItems->at( i );
						CurrentItems->removeAt( i );
					}
			}

		finetuneGui();
	}
