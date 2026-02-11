InitWatch(WatchInfo * info, UINT32 idx)
{
	if(idx > 0)
		info->y = watchList[idx - 1].y + uirotcharheight;
	else
		info->y = 0;
}
