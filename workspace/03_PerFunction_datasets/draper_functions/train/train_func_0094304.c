FindVideoMode(const char *name)
{
    struct VideoMode *vmode;

    for (vmode = VideoModes; vmode; vmode = vmode->next)
	if (!strcmp(name, vmode->name))
	    break;

    return vmode;
}
