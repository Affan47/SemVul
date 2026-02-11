drv_LEDMatrix_init(const char *section, const __attribute__ ((unused))
		       int quiet)
{
    WIDGET_CLASS wc;
    int ret;


    drv_generic_graphic_real_blit = drv_LEDMatrix_blit;


    if ((ret = drv_LEDMatrix_start(section)) != 0)
	return ret;


    if ((ret = drv_generic_graphic_init(section, Name)) != 0)
	return ret;


    wc = Widget_Text;
    wc.draw = drv_generic_graphic_draw;
    widget_register(&wc);


    wc = Widget_Icon;
    wc.draw = drv_generic_graphic_icon_draw;
    widget_register(&wc);


    wc = Widget_Bar;
    wc.draw = drv_generic_graphic_bar_draw;
    widget_register(&wc);


    return 0;
}
