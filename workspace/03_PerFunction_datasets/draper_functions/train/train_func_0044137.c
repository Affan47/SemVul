HandleColormapNotify(void)
{
    XColormapEvent *cevent = (XColormapEvent *) &Event;
    ColormapWindow *cwin, **cwins;
    TwmColormap *cmap;
    int lost, won, n, number_cwins;


    if (XFindContext(dpy, cevent->window, ColormapContext, (XPointer *)&cwin) == XCNOENT)
	return;
    cmap = cwin->colormap;

    if (cevent->new)
    {
	if (XFindContext(dpy, cevent->colormap, ColormapContext,
			 (XPointer *)&cwin->colormap) == XCNOENT)
	    cwin->colormap = CreateTwmColormap(cevent->colormap);
	else
	    cwin->colormap->refcnt++;

	cmap->refcnt--;

	if (cevent->state == ColormapUninstalled)
	    cmap->state &= ~CM_INSTALLED;
	else
	    cmap->state |= CM_INSTALLED;

	if (cmap->state & CM_INSTALLABLE)
	    InstallWindowColormaps(ColormapNotify, (TwmWindow *) NULL);

	if (cmap->refcnt == 0)
	{
	    XDeleteContext(dpy, cmap->c, ColormapContext);
	    free((char *) cmap);
	}

	return;
    }

    if (cevent->state == ColormapUninstalled &&
	(cmap->state & CM_INSTALLABLE))
    {
	if (!(cmap->state & CM_INSTALLED))
	    return;
	cmap->state &= ~CM_INSTALLED;

	if (!ColortableThrashing)
	{
	    ColortableThrashing = TRUE;
	    XSync(dpy, 0);
	}

	if (cevent->serial >= Scr->cmapInfo.first_req)
	{
	    number_cwins = Scr->cmapInfo.cmaps->number_cwins;


	    cwins = Scr->cmapInfo.cmaps->cwins;
	    for (lost = won = -1, n = 0;
		 (lost == -1 || won == -1) && n < number_cwins;
		 n++)
	    {
		if (lost == -1 && cwins[n] == cwin)
		{
		    lost = n;
		    continue;
		}

		if (won == -1 &&
		    cwins[n]->colormap->install_req == cevent->serial)
		{
		    won = n;
		    continue;
		}
	    }


	    if (won != -1)
		if (lost != -1)
		{

		    if (lost > won)
			n = lost*(lost-1)/2 + won;
		    else
			n = won*(won-1)/2 + lost;
		    Scr->cmapInfo.cmaps->scoreboard[n] = 1;
		} else
		{


		    cmap->state |= CM_INSTALLED;
		}
	    else if (lost != -1)
		InstallWindowColormaps(ColormapNotify, (TwmWindow *) NULL);
	    else
		ColortableThrashing = FALSE;
	}
    }

    else if (cevent->state == ColormapUninstalled)
	cmap->state &= ~CM_INSTALLED;

    else if (cevent->state == ColormapInstalled)
	cmap->state |= CM_INSTALLED;
}
