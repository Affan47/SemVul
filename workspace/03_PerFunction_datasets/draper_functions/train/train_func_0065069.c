InitSubtitles(const char* filename)
{
    if (lockThreads("InitSubtitles") == 0)
    {
	if (m_pSubtitles)
	    subtitle_close(m_pSubtitles);
	char* fn = NULL;
	int fd = subtitle_filename(filename, &fn);
	if (fd >= 0)
	{
            char* cp;
	    Get(SUBTITLE_CODEPAGE, &cp, 0);
	    m_pSubtitles = subtitle_open(fd, GetFps(), cp);
	    if (fn)
	    {
		AVM_WRITE("aviplay", "Subtitles from: %s  (codepage: %s)\n", fn, cp);
		free(fn);
	    }
	    if (cp)
                free(cp);
	}
        unlockThreads();
    }
    return 0;
}
