moveOver( const QPointF& pos )
{
	if (!mIsPaletteEnabled)
		return;

	if ( mNeedReorder )
		reorderItems();

	for ( int i = 0 ; i < mInteractions.size() ; i++ )
	{
		if ( mInteractions[i].mPath->contains(pos) )
		{
			if ( mHighlightedInteractionIndex != i )
			{
				mHighlightedInteractionIndex = i;
				update();
			}
			return;
		}
	}

	if ( mHighlightedInteractionIndex != -1 )
	{
		mHighlightedInteractionIndex = -1;
		update();
	}
}
