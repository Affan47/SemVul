SoundOpenFileForWriting(
                        const char *name,
                        Sound           s
                        )
{
    if (SoundFileFormat(s) != SoundFileFormatNone &&
	(_SoundFileInfo[SoundFileFormat(s)].openFileForWriting) (name,
							     s->formatInfo))
    {
        SoundNumSamples(s) = 0;
	return s;
    }

    return NULL;
}
