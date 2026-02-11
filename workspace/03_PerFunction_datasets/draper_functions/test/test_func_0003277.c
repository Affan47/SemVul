DrawLoadMenu(void)
{
    char *title;

    title = DEH_String("LOAD GAME");

    MN_DrTextB(title, 160 - MN_TextBWidth(title) / 2, 10);
    if (!slottextloaded)
    {
        MN_LoadSlotText();
    }
    DrawFileSlots(&LoadMenu);
}
