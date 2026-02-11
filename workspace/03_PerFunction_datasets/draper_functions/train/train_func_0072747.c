afGetByteOrder (AFfilehandle file, int trackid)
{
	if (!_af_filehandle_ok(file))
		return -1;

	Track *track = file->getTrack(trackid);
	if (!track)
		return -1;

	return track->f.byteOrder;
}
