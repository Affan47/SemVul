afInitMarkName(AFfilesetup setup, int trackid, int markid,
	const char *namestr)
{
	int	markno;
	int	length;

	if (!_af_filesetup_ok(setup))
		return;

	TrackSetup *track = setup->getTrack(trackid);
	if (!track)
		return;

	for (markno=0; markno<track->markerCount; markno++)
	{
		if (track->markers[markno].id == markid)
			break;
	}

	if (markno == track->markerCount)
	{
		_af_error(AF_BAD_MARKID, "no marker id %d for file setup", markid);
		return;
	}

	length = strlen(namestr);
	if (length > 255)
	{
		_af_error(AF_BAD_STRLEN,
			"warning: marker name truncated to 255 characters");
		length = 255;
	}

	if (track->markers[markno].name)
		free(track->markers[markno].name);
	if ((track->markers[markno].name = (char *) _af_malloc(length+1)) == NULL)
		return;
	strncpy(track->markers[markno].name, namestr, length);


	track->markers[markno].name[length] = '\0';
}
