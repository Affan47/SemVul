drv_RB_init(const char *section, const int quiet)
{
    WIDGET_CLASS wc;
    int asc255bug;
    int ret;

    info("%s: %s", Name, "$Rev: 771 $");


    XRES = 5;
    YRES = 8;
    CHARS = 8;
    CHAR0 = 0;
    GOTO_COST = 2;


    drv_generic_text_real_write = drv_RB_write;
    drv_generic_text_real_defchar = drv_RB_defchar;
    drv_generic_gpio_real_set = drv_RB_GPO;


    if ((ret = drv_RB_start(section, quiet)) != 0)
	return ret;


    if ((ret = drv_generic_text_init(section, Name)) != 0)
	return ret;


    if ((ret = drv_generic_text_icon_init()) != 0)
	return ret;


    if ((ret = drv_generic_text_bar_init(0)) != 0)
	return ret;


    cfg_number(section, "asc255bug", 0, 0, 1, &asc255bug);
    drv_generic_text_bar_add_segment(0, 0, 255, 32);
    if (!asc255bug)
	drv_generic_text_bar_add_segment(255, 255, 255, 255);


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


    AddFunction("LCD::backlight", -1, plugin_backlight);

    return 0;
}
