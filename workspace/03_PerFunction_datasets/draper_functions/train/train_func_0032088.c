avail_node_enough_for_search(short x1, short y1, short x2, short y2)
{
	short dispX = abs(x1-x2);
	short dispY = abs(y1-y2);

	short majDist = dispX>dispY ? dispX : dispY;
	short minDist = abs(dispX-dispY);

	int nodeRequire = MIN(VALID_BACKGROUND_SEARCH_NODE, majDist<<5);
	int totalNode = seek_path.total_node_avail;
	if(totalNode < nodeRequire)
	{
		if(totalNode>=MIN_BACKGROUND_NODE_USED_UP)
			seek_path.total_node_avail = MIN_BACKGROUND_NODE_USED_UP-1;

		return 0;
	}

	return 1;
}
