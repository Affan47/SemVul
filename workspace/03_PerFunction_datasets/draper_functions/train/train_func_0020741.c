recalculateItemHeight()
{
	IGUISkin*		skin = Environment->getSkin();
	IGUITreeViewNode*	node;

	if( Font != skin->getFont() )
	{
		if( Font )
		{
			Font->drop();
		}

		Font = skin->getFont();
		ItemHeight = 0;

		if( Font )
		{
			ItemHeight = Font->getDimension( L"A" ).Height + 4;
			Font->grab();
		}

		if( IconFont )
		{
			s32 height = IconFont->getDimension( L" " ).Height;
			if( height > ItemHeight )
			{
				ItemHeight = height;
			}
		}
		if( ImageList )
		{
			if( ImageList->getImageSize().Height + 1 > ItemHeight )
			{
				ItemHeight = ImageList->getImageSize().Height + 1;
			}
		}
	}

	IndentWidth = ItemHeight;
	if( IndentWidth < 9 )
	{
		IndentWidth = 9;
	}
	else if( IndentWidth > 15 )
	{
		IndentWidth = 15;
	}
	else
	{
		if( ( ( IndentWidth >> 1 ) << 1 ) - IndentWidth == 0 )
		{
			--IndentWidth;
		}
	}

	TotalItemHeight = 0;
	TotalItemWidth = AbsoluteRect.getWidth() * 2;
	node = Root->getFirstChild();
	while( node )
	{
		TotalItemHeight += ItemHeight;
		node = node->getNextVisible();
	}

	if ( ScrollBarV )
		ScrollBarV->setMax( TotalItemHeight - AbsoluteRect.getHeight() );

	if ( ScrollBarH )
		ScrollBarH->setMax( TotalItemWidth - AbsoluteRect.getWidth() );

}
