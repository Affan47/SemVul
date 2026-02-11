ui_closetopmenu(void)
{
    if (!ui_nmenus)
	return;
    ui_nmenus--;
    ui_closemenu(ui_menus[ui_nmenus]);
    ui_updatestarts();
}
