FullRedisplay()


{
    FBBegin(FB.fDisplay);
    InitViewport();
    InitCoarseWindow(View->kvCoarseWindow->kaX,View->kvCoarseWindow->kaY,
        (int)View->kvCoarseWindow->kaWidth);
    SetCurrentAOI(View->kvCoarseWindow);
    InitFineWindow(View->kvFineWindow->kaX,View->kvFineWindow->kaY);
    InitVLT();
    FBForeground(ERASE,0);
    FBFlood();
    ShowCommandMenu();
    ShowLayerTable();
    ShowParameters();
    if (Parameters.kpCellName[0] != EOS) {
        Redisplay(View->kvCoarseWindow);
        if (Parameters.kpRedisplayControl == SPLITSCREEN)
            XORfineViewport();
    }
    RedrawPrompt();
    FBKbRepaint((1+FB.fLastCursorColumn)*FB.fFontWidth,
        FB.fMaxY - FB.fFontHeight*(FB.fNumRows-2));
}
