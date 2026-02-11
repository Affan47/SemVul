afInitRate (AFfilesetup setup, int trackid, double rate)
{
	if (!_af_filesetup_ok(setup))
		return;

	TrackSetup *track = setup->getTrack(trackid);
	if (!track)
		return;

	if (rate <= 0.0)
	{
		_af_error(AF_BAD_RATE, "invalid sample rate %.30g", rate);
		return;
	}

	track->f.sampleRate = rate;
	track->rateSet = true;
}
