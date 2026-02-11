updateGuiItem()
	{
		ListViewItem->setText( 0, DisplayType );
		ListViewItem->setText( 1, DisplayValue );
		ListViewItem->setToolTip( 0, SettingsManager::instance()->TypeName( DataType, Type ) );

		if ( DataType == "Filter" )
			{
				ListViewItem->setIcon( 0, QIcon( ":/icons/Filter.png" ) );
				ListViewItem->setTextColor( 1, QColor( "gray" ) );
				if ( Options.count() > 0 )
					{
						ListViewItem->setToolTip( 1, tr( "Values of this filter item") );
					}
				else
					{
						ListViewItem->setToolTip( 1, "" );
					}
				return;
			}
		else if ( IsDevice == true )
			{
				ListViewItem->setIcon( 0, QIcon( ":/icons/GpsDevice.png" ) );
				ListViewItem->setTextColor( 1, QColor( "blue" ) );
				ListViewItem->setToolTip( 1, Value );
				return;
			}
		else if ( DataType == "Output" )
			{
				ListViewItem->setIcon( 0, QIcon( ":/icons/Folder.png" ) );
				ListViewItem->setTextColor( 1, QColor( "black" ) );
				ListViewItem->setToolTip( 1, Value );
				return;
			}
		else if ( FileExists == false && DataType == "Input" )
			{
				ListViewItem->setIcon( 0, QIcon( ":/icons/FolderWarning.png" ) );
				ListViewItem->setTextColor( 1, QColor( "red" ) );
				ListViewItem->setToolTip( 1, tr( "Sorry, but the file %1 was not found" ).arg( Value ) );
				return;
			}
		else if ( DataType == "Input" )
			{
				ListViewItem->setIcon( 0, QIcon( ":/icons/Folder.png" ) );
				ListViewItem->setTextColor( 1, QColor( "black" ) );
				ListViewItem->setToolTip( 1, Value );
				return;
			}
		else
			{
				ListViewItem->setIcon( 0, QIcon( ":/icons/Empty.png" ) );
				ListViewItem->setTextColor( 1, QColor( "red" ) );
				ListViewItem->setToolTip( 1, tr( "Sorry, Gebabbel does not know what this item is all about." ) );
				return;
			}

	}
