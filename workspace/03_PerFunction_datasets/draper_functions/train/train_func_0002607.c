add_dirs(prefs_t *p)
{
	char buf[300];
	if(p->dir[0])
	{
		char *upath = fmap->sys2unix(p->dir);
		snprintf(buf, 300, "%s/sfx", upath);
		fmap->addpath("SFX", buf, 1);
		snprintf(buf, 300, "%s/gfx", upath);
		fmap->addpath("GFX", buf, 1);
		snprintf(buf, 300, "%s/scores", upath);
		fmap->addpath("SCORES", buf, 1);
		snprintf(buf, 300, "%s", upath);
		fmap->addpath("CONFIG", buf, 0);
	}

	if(p->sfxdir[0])
		fmap->addpath("SFX", fmap->sys2unix(p->sfxdir), 1);

	if(p->gfxdir[0])
		fmap->addpath("GFX", fmap->sys2unix(p->gfxdir), 1);

	if(p->scoredir[0])
		fmap->addpath("SCORES", fmap->sys2unix(p->scoredir), 1);
}
