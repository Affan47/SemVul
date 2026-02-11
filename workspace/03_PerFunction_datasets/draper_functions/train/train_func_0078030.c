scan_site(int xLoc, int yLoc, int siteType)
{
	Site* sitePtr;
	int   siteDis, minDis=0x7FFFFFFF, nearestSiteRecno=0;

	for( int i=site_array.size() ; i>0 ; i-- )
	{
		if( site_array.is_deleted(i) )
			continue;

		sitePtr = site_array[i];

		if( siteType==0 || sitePtr->site_type==siteType )
		{
			siteDis = misc.points_distance( xLoc, yLoc, sitePtr->map_x_loc, sitePtr->map_y_loc );

			if( siteDis < minDis )
			{
				minDis 		 	  = siteDis;
				nearestSiteRecno = i;
			}
		}
	}

	return nearestSiteRecno;
}
