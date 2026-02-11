deleteRepeatedFeats(
                    CFeatureList            & feat_list )
{
	CFeatureList::iterator	itList1,itList2;
	float					lx = 0.0, ly = 0.0;


	for( itList1 = feat_list.begin(); itList1 != feat_list.end(); itList1++)
	{
		lx = (*itList1)->x;
		ly = (*itList1)->y;
		for( itList2 = itList1; itList2 != feat_list.end(); itList2++)
		{
			if( (lx == (*itList2)->x && ly == (*itList2)->y ) && ( (*itList2)->x > 0.0f && (*itList2)->y > 0.0f ))
			{
				(*itList2)->x = -1.0f;
				(*itList2)->y = -1.0f;
			}
		}
	}


	for( itList1 = feat_list.begin(); itList1 != feat_list.end();)
	{
		if( (*itList1)->x == -1.0f && (*itList1)->y == -1.0f )
			itList1 = feat_list.erase( itList1 );
		else
			itList1++;
	}
}
