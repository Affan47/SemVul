SoundOpenFileForReading(const char *name)
{
    Sound           s;
    int             i;

    if (!(s = (Sound) malloc(sizeof(SoundRec))))
	return NULL;

    SoundComment(s) = NULL;

    for (i = 0; i < SoundNumFileFormats; i++)
	if ((s->formatInfo = (_SoundFileInfo[i].openFileForReading) (name)))
	{
	    if (!(_SoundFileInfo[i].toSound) (s))
	    {
		SoundCloseFile(s);
		return NULL;
	    }
	    break;
	}

    if (i == SoundNumFileFormats)
    {
	SoundCloseFile(s);
	return NULL;
    }

    return s;
}
