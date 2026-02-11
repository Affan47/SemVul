setup (int faces)
{
	if (d->isValid && faces == d->faces)
		return;
	d->faces = faces;
	initialize ();
}
