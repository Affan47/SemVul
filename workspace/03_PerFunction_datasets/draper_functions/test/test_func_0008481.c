drv_M5_init(const char *section, const int quiet)
{
    WIDGET_CLASS wc;
    int ret;

    info("%s: %s", Name, "$Rev: 1174 $");


    XRES = -1;
    YRES = -1;
    CHARS = 0;
    CHAR0 = 248;
    GOTO_COST = 1;


    drv_generic_text_real_write = drv_M5_write;
    drv_generic_text_real_defchar = drv_M5_defchar;
    drv_generic_gpio_real_set = drv_M5_GPO;


    if ((ret = drv_M5_start(section, quiet)) != 0)
	return ret;


    if ((ret = drv_generic_text_init(section, Name)) != 0)
	return ret;


    if ((ret = drv_generic_text_icon_init()) != 0)
	return ret;


    if ((ret = drv_generic_text_bar_init(0)) != 0)
	return ret;


    drv_generic_text_bar_add_segment(0, 0, 255, 32);


    if ((ret = drv_generic_gpio_init(section, Name)) != 0)
	return ret;


    wc = Widget_Text;
    wc.draw = drv_generic_text_draw;
    widget_register(&wc);


    wc = Widget_Icon;
    wc.draw = drv_generic_text_icon_draw;
    widget_register(&wc);


    wc = Widget_Bar;
    wc.draw = drv_generic_text_bar_draw;
    widget_register(&wc);


    return 0;
}
