ui_ministatus(uih_context * uih)
{
    if (ministatuswindow == NULL) {
        ministatuswindow =
            uih_registerw(uih, ui_ministatuspos, ui_drawministatus, NULL,
                          0);
    } else {
        uih_removew(uih, ministatuswindow);
        ministatuswindow = NULL;
    }
    ui_updatestarts();
    ui_updatemenus(uih, "ministatus");
    ui_updatemenus(uih, "animministatus");
}
