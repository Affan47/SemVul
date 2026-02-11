init_property_menu()

{
    int i = 0;
    int NumPropertyMenu = 13;

    if (PropertyMenu == NULL)
        PropertyMenu = (MENU *) tmalloc(NumPropertyMenu*sizeof(MENU));
    memset(PropertyMenu,0,NumPropertyMenu*sizeof(MENU));

    PropertyMenu[i++].mEntry = MenuHELP;
    PropertyMenu[i++].mEntry = MenuSpace;
    PropertyMenu[i++].mEntry = MenuBASIC;
    PropertyMenu[i++].mEntry = MenuSpace;
    PropertyMenu[i++].mEntry = MenuLAYER;

    PropertyMenu[i++].mEntry = MenuAREA;
    PropertyMenu[i++].mEntry = MenuSELEC;
    PropertyMenu[i++].mEntry = MenuDESEL;
    PropertyMenu[i++].mEntry = MenuSpace;
    PropertyMenu[i++].mEntry = MenuSHOW;

    PropertyMenu[i++].mEntry = MenuADPRP;
    PropertyMenu[i++].mEntry = MenuRMPRP;
    PropertyMenu[i++].mEntry = NULL;
}
