Visib(LookedAhead)

int *LookedAhead;
{
    extern char *MenuVISIB;

    MenuSelect(MenuVISIB);
    ShowPrompt("Point at layers to toggle visibility.");
    NoMakeVisible = True;
    loop {
        switch (PointLoopLayer(LookedAhead)) {
        case PL_PLT:
            if (LayerTable[Parameters.kpLayer].klAttributes & VISIBLE)
                MakeLayerInvisible(Parameters.kpLayer);
            else
                MakeLayerVisible(Parameters.kpLayer);
            break;
        case PL_ESC:
        case PL_CMD:
            MenuDeselect(MenuVISIB);
            NoMakeVisible = False;
            ErasePrompt();
            return;
        }
    }
}
