Togl_Render(ClientData clientData)
{
    Togl   *togl = (Togl *) clientData;

    if (togl->DisplayProc) {

#ifdef TOGL_AGL_CLASSIC


        MacRegion r;
        RgnPtr  rp = &r;
        GrafPtr curPort, parentWin;

        parentWin = (GrafPtr)
                (((MacDrawable *) (Tk_WindowId(togl->TkWin)))->toplevel->
                portPtr);
        if (!parentWin)
            return;
#endif

        Togl_MakeCurrent(togl);

#ifdef TOGL_AGL_CLASSIC

        GetPort(&curPort);
        SetPort(parentWin);
        r.rgnBBox.left = ((TkWindow *) (togl->TkWin))->privatePtr->xOff;
        r.rgnBBox.right =
                r.rgnBBox.left + ((TkWindow *) (togl->TkWin))->changes.width -
                1;
        r.rgnBBox.top = ((TkWindow *) (togl->TkWin))->privatePtr->yOff;
        r.rgnBBox.bottom =
                r.rgnBBox.top + ((TkWindow *) (togl->TkWin))->changes.height -
                1;
        r.rgnSize = sizeof (Region);
        InvalRgn(&rp);
        SetClip(&rp);


        SetMacBufRect(togl);
#endif

#ifdef TOGL_AGL
        SetMacBufRect(togl);
#endif

        togl->DisplayProc(togl);

#ifdef TOGL_AGL_CLASSIC
        SetPort(curPort);
#endif

    }
#if defined(TOGL_AGL_CLASSIC) || defined(TOGL_AGL)
    else {

        SetMacBufRect(togl);
    }
#endif
    togl->UpdatePending = False;
}
