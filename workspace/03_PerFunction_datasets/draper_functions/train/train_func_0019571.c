l_chooseDisplayProg(l_int32  selection)
{
    if (selection == L_DISPLAY_WITH_XLI ||
        selection == L_DISPLAY_WITH_XZGV ||
        selection == L_DISPLAY_WITH_XV ||
        selection == L_DISPLAY_WITH_IV ||
        selection == L_DISPLAY_WITH_OPEN) {
        var_DISPLAY_PROG = selection;
    } else {
        L_ERROR("invalid display program\n", "l_chooseDisplayProg");
    }
    return;
}
