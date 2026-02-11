XdbeGetVisualInfo (
    Display        *dpy,
    Drawable       *screen_specifiers,
    int            *num_screens)
{
    XExtDisplayInfo *info = find_display(dpy);
    register xDbeGetVisualInfoReq *req;
    xDbeGetVisualInfoReply rep;
    XdbeScreenVisualInfo *scrVisInfo;
    int i;

    DbeCheckExtension (dpy, info, (XdbeScreenVisualInfo *)NULL);

    LockDisplay (dpy);

    DbeGetReq(DbeGetVisualInfo, req, info);
    req->length = 2 + *num_screens;
    req->n      = *num_screens;
    Data32 (dpy, screen_specifiers, (*num_screens * sizeof (CARD32)));

    if (!_XReply (dpy, (xReply *) &rep, 0, xFalse)) {
        UnlockDisplay (dpy);
        SyncHandle ();
        return NULL;
    }


    if (*num_screens == 0)
       *num_screens = rep.m;


    if ((*num_screens > 0) && (*num_screens < 65536))
        scrVisInfo = Xmalloc(*num_screens * sizeof(XdbeScreenVisualInfo));
    else
        scrVisInfo = NULL;
    if (scrVisInfo == NULL) {
        _XEatDataWords(dpy, rep.length);
        UnlockDisplay (dpy);
        SyncHandle ();
        return NULL;
    }

    for (i = 0; i < *num_screens; i++)
    {
        int j;
        unsigned long c;

        _XRead32 (dpy, (long *) &c, sizeof(CARD32));

        if (c < 65536) {
            scrVisInfo[i].count = c;
            scrVisInfo[i].visinfo = Xmalloc(c * sizeof(XdbeVisualInfo));
        } else
            scrVisInfo[i].visinfo = NULL;


        if (scrVisInfo[i].visinfo == NULL) {
            for (j = 0; j < i; j++) {
                Xfree ((char *)scrVisInfo[j].visinfo);
            }
            Xfree ((char *)scrVisInfo);
            _XEatDataWords(dpy, rep.length);
            UnlockDisplay (dpy);
            SyncHandle ();
            return NULL;
        }


        for (j = 0; j < scrVisInfo[i].count; j++) {
            xDbeVisInfo xvi;

            _XRead (dpy, (char *)&xvi, sizeof(xDbeVisInfo));
            scrVisInfo[i].visinfo[j].visual    = xvi.visualID;
            scrVisInfo[i].visinfo[j].depth     = xvi.depth;
            scrVisInfo[i].visinfo[j].perflevel = xvi.perfLevel;
        }

    }

    UnlockDisplay (dpy);
    SyncHandle ();
    return scrVisInfo;

}
