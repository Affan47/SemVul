Blink(LookedAhead)

int *LookedAhead;
{
    int Layer;
    extern char *MenuBLINK;

    MenuSelect(MenuBLINK);

    if (! FB.fBlinkers) {
        ShowPrompt("Sorry, blinking layers are not available.");
        *LookedAhead = False;
        MenuDeselect(MenuBLINK);
        return;
    }
    ShowPrompt("Point to EACH layer you want to be blinking.");
    for (Layer = 1; Layer <= NumLayerTable; Layer++) {
        LayerTable[Layer].klAttributes &= ~BLINK;
        FBBlink(Layer,0,0,0,0);
    }
    loop {
        Point();
        if (Parameters.kpPointLayerTable)
            LayerTable[Parameters.kpLayer].klAttributes |= BLINK;
        else {
            *LookedAhead = True;
            MenuDeselect(MenuBLINK);
            return;
        }
    }
}
