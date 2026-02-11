getTrack(int trackID)
{
	for (int i=0; i<trackCount; i++)
	{
		if (tracks[i].id == trackID)
			return &tracks[i];
	}

	_af_error(AF_BAD_TRACKID, "bad track id %d", trackID);
	return NULL;
}
