drv_TeakLCM_init(const char *section, const int quiet)
{
    WIDGET_CLASS wc;
    int ret;

    info("%s: %s (quiet=%d)", Name, "$Rev$", quiet);


    XRES = 5;
    YRES = 8;
    CHARS = 0;
    CHAR0 = 0;
    GOTO_COST = -1;


    drv_generic_text_real_write = drv_TeakLCM_write;


    if ((ret = drv_TeakLCM_start(section)) != 0)
	return ret;


    if ((ret = drv_generic_text_init(section, Name)) != 0)
	return ret;


    wc = Widget_Text;
    wc.draw = drv_generic_text_draw;
    widget_register(&wc);


    return 0;
}
