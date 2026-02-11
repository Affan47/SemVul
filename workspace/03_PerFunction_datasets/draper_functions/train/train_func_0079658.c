Windo(LookedAhead)

int *LookedAhead;
{
    int NewWindowWidth, Width, Height, Tmp;
    MenuSelect(MenuWINDO);
    loop {
        ShowPrompt("Point to endpoints of diagonal.");
        switch (PointLoopSafe(LookedAhead)) {
        case PL_ESC:
        case PL_CMD:
            goto quit;
        case PL_PCW:
            break;
        }
        FBSetRubberBanding('R');
        switch (PointLoopSafe(LookedAhead)) {
        case PL_ESC:
        case PL_CMD:
            FBSetRubberBanding(0);
            goto quit;
        case PL_PCW:
            FBSetRubberBanding(0);
            break;
        }
        SaveLastView();


        Width = KicCursor.kcX - KicCursor.kcPredX;
        Height = KicCursor.kcY - KicCursor.kcPredY;
        if (Width < 0) Width = -Width;
        if (Height < 0) Height = -Height;

        Tmp = Height * View->kvCoarseViewport->kaWidth/
            View->kvCoarseViewport->kaHeight;
        NewWindowWidth = max(Width,Tmp);

        Height /= 2;
        Width /= 2;

        if (NewWindowWidth <= 0)    NewWindowWidth = RESOLUTION;
        InitCoarseWindow( min(KicCursor.kcX,KicCursor.kcPredX)+Width,
            min(KicCursor.kcY,KicCursor.kcPredY)+Height,NewWindowWidth);

        InitFineWindow(min(KicCursor.kcX,KicCursor.kcPredX)+Width,
            min(KicCursor.kcY,KicCursor.kcPredY)+Height);

        SetPositioning();
        ShowParameters();
        RedisplayViewports();
        FBTransfer();
    }
quit:
    MenuDeselect(MenuWINDO);
    ErasePrompt();
}
