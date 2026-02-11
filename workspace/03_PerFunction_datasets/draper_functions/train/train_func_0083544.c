stripFirstFrame()
{
	detach();
	if ( numFrames() > 1 ) {
		d->frames.takeFirst();

		if ( !paused() )
			restart();
	}
}
