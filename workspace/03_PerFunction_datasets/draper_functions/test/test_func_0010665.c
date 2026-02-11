mousetype(int m)
{
#ifdef _plan9_
#define filevisible 0
#endif
    if (ui_nmenus || helpvisible || filevisible || dialogvisible
        || yesnodialogvisible)
        m = NORMALMOUSE;
    if (mouse != m) {
        mouse = m;
        if (driver->mousetype != NULL)
            driver->mousetype(m);
    }
}
